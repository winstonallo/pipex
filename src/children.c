/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:12:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 11:21:03 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	give_birth1(t_list *data, char **command_arguments, char **envp)
{
	if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
		perror("dup child 1");
	close(data->pipe[0]);
	dup2(data->input_fd, STDIN_FILENO);
	if (execve(data->input_path, command_arguments, envp) == -1)
		perror("child 1");
}

void	give_birth2(t_list *data, char **command_arguments, char **envp)
{
	if (dup2(data->pipe[0], STDIN_FILENO) == -1)
		perror("dup child 1");
	close(data->pipe[1]);
	dup2(data->output_fd, STDOUT_FILENO);
	if (execve(data->output_path, command_arguments, envp) == -1)
		perror("child 2");
}
