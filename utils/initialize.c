/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:19:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 22:05:24 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_files(char **argv, t_list *data)
{
	int	open_fail;

	open_fail = 0;
	data->input_fd = open(argv[1], O_RDONLY);
	if (data->input_fd == -1)
	{
		write(2, data->input_command, ft_strlen(data->input_command));
		write(2, ": ", 2);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": ", 2);
		perror("");
		open_fail = 1;
	}
	data->output_fd = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (data->output_fd == -1)
		return(perror("outfile"), 1);
	if (open_fail == 0)
		return (0);
	return (-1);
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
