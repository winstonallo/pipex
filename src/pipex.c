/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/04 10:10:24 by abied-ch         ###   ########.fr       */
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
	close(data->fd[0]);
	close(data->fd[1]);
	free(data->fd);
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
	dup2(data->fd[1], 1);
	close(data->fd[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	initialize_fd(char **argv, t_list *data)
{
	data->fd = malloc(2 * sizeof(int));
	data->fd[0] = open(argv[1], O_RDONLY);
	if (data->fd[0] == -1)
	{
		perror("open");
		return ;
	}
	data->fd[1] = open(argv[4], O_WRONLY);
	if (data->fd[1] == -1)
	{
		perror("open");
		return ;
	}
}

void	initialize_data(t_list *data)
{	
	data->process_id1 = -1;
	data->process_id2 = -1;
	data->paths = NULL;
	data->fd = NULL;
	data->input_path = NULL;
	data->output_path = NULL;
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
		return (-1);
	data->input_path = get_path(argv[2], data);
	if (!data->input_path)
		return (-1);
	data->output_path = get_path(argv[3], data);
	if (!data->output_path)
		return (-1);
	initialize_fd(argv, data);
	if (!data->fd)
		return (-1);
	args[0] = argv[1];
	args[1] = NULL;
	data->process_id1 = fork();
	if (data->process_id1 == 0)
		give_birth1(data, args, envp);
	waitpid(data->process_id1, NULL, 0);
	cleanup(data);
	return (0);
}
