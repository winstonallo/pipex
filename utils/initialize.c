/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:19:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 11:22:45 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(char **argv, t_list *data)
{
	data->input_fd = open(argv[1], O_RDONLY);
	if (data->input_fd == -1)
	{
		perror("open");
		return ;
	}
	data->output_fd = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (data->output_fd == -1)
	{
		perror("open");
		return ;
	}
}

void	initialize_data(t_list *data)
{
	data->process_id1 = -1;
	data->process_id2 = -1;
	data->input_fd = -1;
	data->output_fd = -1;
	data->paths = NULL;
	data->input_path = NULL;
	data->output_path = NULL;
}
