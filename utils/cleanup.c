/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:17:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/06 17:44:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	close_pipes(t_dumpster *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}

static void	ft_free_array(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

int	cleanup(t_dumpster *data)
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
	if (data->input_command)
		free(data->input_command);
	if (data->output_command)
		free(data->output_command);
	close_pipes(data);
	if (data)
		free(data);
	return (0);
}
