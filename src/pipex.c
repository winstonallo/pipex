/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 13:29:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*data;

	if (argc != 5)
		ft_putendl_fd("Error: Too many arguments", 2);
	data = malloc(sizeof(t_list));
	if (!data)
		return (-1);
	initialize_data(data);
	parse_environment(envp, data);
	if (!data->paths)
		error("Parse Environment", data);
	initialize_args(argv, data);
	data->input_path = get_path(data->input_command, data);
	if (!data->input_path)
		error("Input Path", data);
	data->output_path = get_path(data->output_command, data);
	if (!data->output_path)
		error("Output Path", data);
	if (pipe(data->pipe) < 0)
		error("Pipe", data);
	open_files(argv, data);
	data->process_id1 = fork();
	if (data->process_id1 == 0)
		give_birth1(data, envp);
	data->process_id2 = fork();
	if (data->process_id2 == 0)
		give_birth2(data, envp);
	close_pipes(data);
	waitpid(data->process_id1, NULL, 0);
	waitpid(data->process_id2, NULL, 0);
	cleanup(data);
	return (0);
}
