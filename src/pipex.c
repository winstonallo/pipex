/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:26:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/29 21:39:56 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd_input;
	int		fd_output;
	char	*str;
	
	while (argc)
		break ;
	fd_input = open(argv[1], O_RDONLY);
	dup2(fd_input, 0);
	str = get_next_line(fd_input);
	fd_output = open(argv[4], O_WRONLY);
	dup2(fd_output, 1);
	execve(str, argv, envp);
	close(fd_input);
	close(fd_output);
	return (0);
}
