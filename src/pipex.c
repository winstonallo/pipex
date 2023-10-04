/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/04 13:51:06 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


int	parse_environment(char **envp, t_list *data)
{
	char		**temp;

	temp = envp;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
		{
			*envp += 5;
			data->paths = ft_split(*envp, ':');
			if (!data->paths)
				return (-1);
			
		}
		envp++;
	}
	envp = temp;
	return (0);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	cleanup(t_list *data)
{
	if (data->paths)
		ft_free_array(data->paths);
	if (data->input_path)
		free(data->input_path);
	if (data->output_path)
		free(data->output_path);
	free(data);
}

char	*get_path(char *command, t_list *data)
{
	int		i;
	char	*final_path;

	if (!data->paths)
		return (NULL);
	i = -1;
	command = ft_strjoin("/", command);
	if (!command)
		return (NULL);
	while (data->paths[++i])
	{
		final_path = ft_strjoin(data->paths[i], command);
		if (!final_path)
			return (NULL);
		if (access(final_path, X_OK) == 0)
		{
			free(command);
			return (final_path);
		}
		free(final_path);
	}
	return (NULL);
}

void	give_birth1(t_list *data, char **command_arguments, char **envp)
{
	if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
		perror("dup child 1");
	close(data->pipe[0]);
	dup2(data->input_fd, STDIN_FILENO);
	if (execve(data->input_path, command_arguments, envp) == -1)
		perror("child 1");
}

void	give_birth2(t_list *data, char **command_arguments, char **envp)
{
	if (dup2(data->pipe[0], STDIN_FILENO) == -1)
		perror("dup child 1");
	close(data->pipe[1]);
	dup2(data->output_fd, STDOUT_FILENO);
	if (execve(data->output_path, command_arguments, envp) == -1)
		perror("child 2");
}



void	open_files(char **argv, t_list *data)
{
	data->input_fd = open(argv[1], O_RDONLY);
	if (data->input_fd == -1)
	{
		perror("open");
		return ;
	}
	data->output_fd = open(argv[4], O_WRONLY);
	if (data->output_fd == -1)
	{
		perror("open");
		return ;
	}
}

void	initialize_data(t_list *data)
{	
	data->process_id1 = -1;
	data->process_id2 = -1;
	data->input_fd = -1;
	data->output_fd = -1;
	data->paths = NULL;
	data->input_path = NULL;
	data->output_path = NULL;
}

void	close_pipes(t_list *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*args[2];
	t_list	*data;

	if (argc != 5)
		return (-1);
	data = malloc(sizeof(t_list));
	if (!data)
		return (-1);
	initialize_data(data);
	parse_environment(envp, data);
	if (!data->paths)
	{
		perror("path parsing");
		return (-1);
	}
	data->input_path = get_path(argv[2], data);
	if (!data->input_path)
	{
		perror("input path");
		return (-1);
	}
	data->output_path = get_path(argv[3], data);
	if (!data->output_path)
	{
		perror("output path");
		return (-1);
	}
	if (pipe(data->pipe) < 0)
	{
		perror("pipe");
		return (-1);
	}	
	open_files(argv, data);
	args[0] = argv[1];
	args[1] = NULL;
	data->process_id1 = fork();
	if (data->process_id1 == 0)
		give_birth1(data, args, envp);
	data->process_id2 = fork();
	if (data->process_id2 == 0)
		give_birth2(data, args, envp);
	close_pipes(data);
	waitpid(data->process_id1, NULL, 0);
	waitpid(data->process_id2, NULL, 0);
	cleanup(data);
	return (0);
}
