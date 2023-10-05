/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 11:22:29 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	get_input_args(argv, data);
	get_output_args(argv, data);
	data->input_path = get_path(data->input_command, data);
	if (!data->input_path)
	{
		perror("input path");
		return (-1);
	}
	data->output_path = get_path(data->output_command, data);
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
