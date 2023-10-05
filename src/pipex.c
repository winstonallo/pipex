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


void	exec_input(t_list *data, char **envp)
{
	if (execve(data->input_path, data->input_args, envp) == -1)
	{
		perror("execve");
		cleanup(data);
		exit(0);
	}
}

void	exec_output(t_list *data, char **envp)
{
	if (execve(data->output_path, data->output_args, envp) == -1)
	{
		perror("execve");
		cleanup(data);
		exit(0);
	}
}

void	firstborn(t_list *data, char **envp)
{
	dup2(data->input_fd, STDIN_FILENO);
	dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[0]);
	exec_input(data, envp);
}

void	mommy(t_list *data, char **envp)
{
	dup2(data->output_fd, STDOUT_FILENO);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[1]);
	exec_output(data, envp);
}

int	pipex(t_list *data, char **argv, char **envp)
{
	initialize_args(argv, data);
	open_files(argv, data);
	parse_environment(envp, data);
	data->input_path = get_path(data->input_command, data);
	data->output_path = get_path(data->output_command, data);
	return (0);
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
	if (pipex(data, argv, envp) == -1)
		exit(1);
	data->process_id = fork();
	if (data->process_id == -1)
	{
		perror("fork");
		exit(1);
	}
	if (data->process_id == 0)
		firstborn(data, envp);
	waitpid(data->process_id, NULL, 0);	
	mommy(data, envp);
}

/*int	pipex(t_list *data, char **envp, char **argv)
{
	if (pipe(data->pipe) == -1)
		return (perror("Pipe"), cleanup(data), -1);
	initialize_data(data);
	parse_environment(envp, data);
	if (!data->paths)
		return (perror("Paths"), cleanup(data), -1);
	initialize_args(argv, data);
	open_files(argv, data);
	data->input_path = get_path(data->input_command, data);
	if (!data->input_path)
		return (perror("Input path"), cleanup(data), -1);
	data->output_path = get_path(data->output_command, data);
	if (!data->output_path)
		return (perror("Output path"), cleanup(data), -1);
	data->process_id1 = fork();
	if (data->process_id1 == 0)
		give_birth1(data, envp);
	parent(data, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*data;

	if (argc != 5)
		return (ft_putendl_fd("Error: Invalid number of arguments", 2), 1);
	data = malloc(sizeof(t_list));
	if (!data)
		exit (-1);
	if (pipex(data, envp, argv) == -1)
		exit(-1);
	close_pipes(data);
	cleanup(data);
	return (0);
}
*/