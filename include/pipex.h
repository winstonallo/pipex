/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:27:08 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/06 13:21:33 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_dumpster
{
	char			**paths;
	char			*input_path;
	char			*output_path;
	int				pipe[2];
	pid_t			process_id;
	int				input_fd;
	int				output_fd;
	char			**input_args;
	char			**output_args;
	char			*input_command;
	char			*output_command;
}	t_dumpster;

int		main(int argc, char **argv, char **envp);
void	firstborn(t_dumpster *data, char **envp, char **argv);
void	mommy(t_dumpster *data, char **envp, char **argv);
int		initialize_args(char **argv, t_dumpster *data);
char	*get_path(char *command, t_dumpster *data);
int		parse_environment(char **envp, t_dumpster *data);
int		cleanup(t_dumpster *data);
void	initialize_data(t_dumpster *data);
int		open_files(char *file_name, int fd, t_dumpster *data);
void	initialize_dumpster(t_dumpster *data);

#endif