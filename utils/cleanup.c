/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:17:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 15:16:22 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	cleanup(t_list *data)
{
	if (data->paths)
		ft_free_array(data->paths);
	if (data->input_args)
		ft_free_array(data->input_args);
	if (data->output_args)
		ft_free_array(data->output_args);
	if (data->input_path)
		free(data->input_path);
	if (data->output_path)
		free(data->output_path);
	free(data);
	return (-1);
}

void	close_pipes(t_list *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}
