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

void	fuck_mich_nich_ab_jz(char *s, char **a, char **e, t_list *d)
{
	if (execve(s, a, e) == -1)
	{
		perror("execve");
		cleanup(d);
		exit(0);
	}
}

void	firstborn(t_list *data, char **envp, char **argv)
{
	open_files(argv[4], 0, data);
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
	{
		perror("firstborn dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
	{
		perror("firstborn dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	close(data->pipe[0]);
	fuck_mich_nich_ab_jz(data->input_path, data->input_args, envp, data);
}

void	mommy(t_list *data, char **envp, char **argv)
{
	open_files(argv[4], 1, data);
	if (dup2(data->output_fd, STDOUT_FILENO) == -1)
	{
		perror("mommy dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->pipe[0], STDIN_FILENO) == -1)
	{
		perror("mommy dup2");
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	close(data->pipe[1]);
	fuck_mich_nich_ab_jz(data->output_path, data->output_args, envp, data);
}

