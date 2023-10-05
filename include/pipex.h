/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:27:08 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 11:20:07 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

int		main(int argc, char **argv, char **envp);
void	give_birth1(t_list *data, char **command_arguments, char **envp);
void	give_birth2(t_list *data, char **command_arguments, char **envp);
int		get_output_args(char **argv, t_list *data);
int		get_input_args(char **argv, t_list *data);
char	*get_path(char *command, t_list *data);
int		parse_environment(char **envp, t_list *data);
void	close_pipes(t_list *data);
void	cleanup(t_list *data);
void	ft_free_array(char **arr);
void	initialize_data(t_list *data);
void	open_files(char **argv, t_list *data);

#endif