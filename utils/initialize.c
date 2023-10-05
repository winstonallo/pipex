/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:19:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 19:31:01 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_files(char **argv, t_list *data)
{
	data->input_fd = open(argv[1], O_RDONLY);
	if (data->input_fd == -1)
		return(perror("Infile"), -1);
	data->output_fd = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (data->output_fd == -1)
		return(perror("Outfile"), 1);
	return (0);
}

void	initialize_data(t_list *data)
{
	data->process_id1 = -1;
	data->process_id2 = -1;
	data->input_fd = -1;
	data->output_fd = -1;
	data->input_path = NULL;
	data->output_path = NULL;
}
