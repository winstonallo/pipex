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

void	pipex(t_dumpster *data, char **argv, char **envp)
{
	initialize_args(argv, data);
	parse_environment(envp, data);
	data->input_path = get_path(data->input_command, data);
	data->output_path = get_path(data->output_command, data);
}

int	main(int argc, char **argv, char **envp)
{
	t_dumpster *data;

	data = malloc(sizeof(t_dumpster));
	if (!data)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (argc != 5)
	{
		ft_putendl_fd("Error: Too many arguments(./pipex in c1 c2 out)", 2);
		exit(EXIT_FAILURE);
	}	
	if (pipe(data->pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pipex(data, argv, envp);
	data->process_id = fork();
	if (data->process_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (data->process_id == 0)
		firstborn(data, envp, argv);
	mommy(data, envp, argv);
}
