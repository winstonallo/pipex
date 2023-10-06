/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:19:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/06 17:44:56 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(char *file_name, int fd, t_dumpster *data)
{
	if (fd == 0)
	{
		data->input_fd = open(file_name, O_RDONLY);
		if (data->input_fd == -1)
		{
			perror("open infile");
		}
	}
	else if (fd == 1)
	{
		data->output_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0000644);
		if (data->output_fd == -1)
		{
			perror("open outfile");
			cleanup(data);
			exit(EXIT_FAILURE);
		}
	}
}

void	initialize_dumpster(t_dumpster *data)
{
	data->input_args = NULL;
	data->output_args = NULL;
	data->input_command = NULL;
	data->output_command = NULL;
	data->input_fd = -1;
	data->output_fd = -1;
	data->output_path = NULL;
	data->input_path = NULL;
}
