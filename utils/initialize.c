/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:19:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 22:57:22 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_files(char *file_name, int fd, t_list *data)
{
	int	open_fail;

	open_fail = 0;
	if (fd == 0)
	{
		data->input_fd = open(file_name, O_RDONLY);
		if (data->input_fd == -1)
		{
			write(2, file_name, ft_strlen(file_name));
			write(2, ": ", 2);
			perror("");
			open_fail = 1;
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
	if (open_fail == 0)
		return (0);
	cleanup(data);
	exit (EXIT_FAILURE);
}

