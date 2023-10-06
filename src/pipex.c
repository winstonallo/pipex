/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/06 16:09:20 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(t_dumpster *data, char **argv, char **envp)
{
	initialize_dumpster(data);
	initialize_args(argv, data);
	parse_environment(envp, data);
	data->input_path = get_path(data->input_command, data);
	data->output_path = get_path(data->output_command, data);
}

void	error(t_dumpster *data, char *msg)
{
	free(data);
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static void	forky(t_dumpster *data, char **argv, char **envp)
{
	data->process_id = fork();
	if (data->process_id == -1)
	{
		perror("fork");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	if (data->process_id == 0)
		firstborn(data, envp, argv);
	mommy(data, envp, argv);
}

int	main(int argc, char **argv, char **envp)
{
	t_dumpster	*data;

	data = malloc(sizeof(t_dumpster));
	if (!data)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (argc != 5)
		error(data, "Invalid Input -- (./pipex infile cm1 cmd2 outfile)");
	if (pipe(data->pipe) == -1)
	{
		perror("pipe");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	pipex(data, argv, envp);
	forky(data, argv, envp);
}
