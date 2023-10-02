/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/02 19:24:39 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**parse_environment(char **envp)
{
	char	**paths;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
		{
			*envp += 5;
			paths = ft_split(*envp, ':');
			if (!paths)
				return (NULL);
		}
		envp++;
	}
	return (paths);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	*get_path(char **environment, char *command)
{
	int		i;
	char	*final_path;
	char	**paths;

	paths = parse_environment(environment);
	if (!paths)
		return (NULL);
	i = -1;
	command = ft_strjoin("/", command);
	if (!command)
		return (NULL);
	while (paths[++i])
	{
		final_path = ft_strjoin(paths[i], command);
		if (!final_path)
			return (NULL);
		if (access(final_path, X_OK) == 0)
		{
			ft_free_array(paths);
			free(command);
			return (final_path);
		}
		free(final_path);
	}
	return (NULL);
}

int	give_birth(char *command_path, char **command_arguments)
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
	{
		perror("Fork");
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

int	main(int argc, char **argv, char **envp)
{
	char	*args[2];
	int		fd_input;
	pid_t	process_id;
	char	*command_path;

	while (argc)
		break ;
	command_path = get_path(envp, argv[2]);
	if (!command_path)
		return (-1);
	fd_input = open(argv[1], O_RDONLY);
	if (fd_input == -1)
	{
		perror("open");
		return (-1);
	}
	args[0] = argv[1];
	args[1] = NULL;
	process_id = give_birth(command_path, args);
	if (process_id != 0)
		wait(NULL);
	free(command_path);
	return (0);
}
