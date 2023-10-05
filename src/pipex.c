/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 23:39:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute(char *command_path, char ** args, char **envp, t_list *data)
{
	if (execve(command_path, args, envp) == -1)
	{
		perror("execve");
		cleanup(data);
		exit(0);
	}
}

void	firstborn(t_list *data, char **envp, char **argv)
{
	open_files(argv[4], 0, data);
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
	{
		perror("firstborn dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
	{
		perror("firstborn dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	close(data->pipe[0]);
	execute(data->input_path, data->input_args, envp, data);
}

void	mommy(t_list *data, char **envp, char **argv)
{
	open_files(argv[4], 1, data);
	if (dup2(data->output_fd, STDOUT_FILENO) == -1)
	{
		perror("mommy dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->pipe[0], STDIN_FILENO) == -1)
	{
		perror("mommy dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	close(data->pipe[1]);
	execute(data->output_path, data->output_args, envp, data);
}

void	pipex(t_list *data, char **argv, char **envp)
{
	initialize_args(argv, data);
	parse_environment(envp, data);
	data->input_path = get_path(data->input_command, data);
	data->output_path = get_path(data->output_command, data);
}

int	main(int argc, char **argv, char **envp)
{
	t_list *data;

	data = malloc(sizeof(t_list));
	if (argc != 5)
	{
		ft_putendl_fd("Error: Too many arguments(./pipex in c1 c2 out)", 2);
		exit(1);
	}	
	if (pipe(data->pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pipex(data, argv, envp);
	data->process_id = fork();
	if (data->process_id == -1)
	{
		perror("fork");
		exit(1);
	}
	if (data->process_id == 0)
		firstborn(data, envp, argv);
	mommy(data, envp, argv);
}
