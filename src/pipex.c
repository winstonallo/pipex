/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 22:04:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipex(t_list *data, char **envp, char **argv)
{
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
	if (pipe(data->pipe) < 0)
		return (perror("Pipe"), cleanup(data), -1);
	data->process_id1 = fork();
	if (data->process_id1 == 0)
		give_birth1(data, envp);
	data->process_id2 = fork();
	if (data->process_id2 == 0)
		give_birth2(data, envp);	
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
	if (data->process_id1 == 0)
		waitpid(data->process_id1, NULL, 0);
	if (data->process_id2 == 0)
		waitpid(data->process_id2, NULL, 0);
	cleanup(data);
	return (0);
}
