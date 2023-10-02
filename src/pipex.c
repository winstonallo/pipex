/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/02 22:16:05 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_list	*parse_environment(char **envp)
{
	static char	**paths;
	t_list		*new;
	char		**temp;
	
	temp = envp;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
		{
			*envp += 5;
			paths = ft_split(*envp, ':');
			if (!paths)	
				return (NULL);
			new = ft_lstnew((char **)paths);
		}
		envp++;
	}
	envp = temp;
	return (new);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
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
	}
	return (NULL);
}

int	give_birth(char *command_path, char **command_arguments)
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (process_id == 0)
	{
		if (execve(command_path, command_arguments, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	return (process_id);
}

int	*initialize_fd(char **argv)
{
	int	*fd;
	
	fd = malloc(2 * sizeof(int));
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
		perror("open");
		return (NULL);
	}
	fd[1] = open(argv[4], O_WRONLY);
	if (fd[1] == -1)
	{
		perror("open");
		return (NULL);
	}
	return (fd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*args[2];
	int		*fd;
	pid_t	process_id;
	t_list	*data;

	while (argc)
		break ;
	data = parse_environment(envp);
	if (!data)
		return (-1);
	data->input_path = get_path(argv[2], data);
	if (!data->input_path)
		return (-1);
	data->output_path = get_path(argv[3], data);
	if (!data->output_path)
		return (-1);
	fd = initialize_fd(argv);
	if (!fd)
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	args[0] = argv[1];
	args[1] = NULL;
	process_id = give_birth(data->input_path, args);
	if (process_id != 0)
		wait(0);
	free(data->input_path);
	free(data->output_path);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
