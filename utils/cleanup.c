/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:17:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 11:22:50 by abied-ch         ###   ########.fr       */
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

void	cleanup(t_list *data)
{
	if (data->paths)
		ft_free_array(data->paths);
	if (data->input_path)
		free(data->input_path);
	if (data->output_path)
		free(data->output_path);
	free(data);
}

void	close_pipes(t_list *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}
