/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:12:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 22:34:05 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	give_birth1(t_list *data, char **envp)
{
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
		perror("DUP2 child 1");
	dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[0]);
	if (execve(data->input_path, data->input_args, envp) == -1)
		perror("EXECVE child 1");		
}

void	parent(t_list *data, char **envp)
{
	if (dup2(data->output_fd, STDOUT_FILENO) == -1)
		perror("DUP2 child 2");
	dup2(data->pipe[0], 0);
	close(data->pipe[1]);
	if (execve(data->output_path, data->output_args, envp) == -1)
		perror("EXECVE child 2");
}

