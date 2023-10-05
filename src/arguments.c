/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:14:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 13:19:19 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parse_environment(char **envp, t_list *data)
{
	char		**temp;

	temp = envp;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
		{
			*envp += 5;
			data->paths = ft_split(*envp, ':');
			if (!data->paths)
				return (-1);
		}
		envp++;
	}
	envp = temp;
	return (0);
}

char	*get_path(char *command, t_list *data)
{
	int		i;
	char	*final_path;

	if (!data->paths)
		return (NULL);
	i = -1;
	command = ft_strjoin("/", command);
	if (!command)
		return (NULL);
	while (data->paths[++i])
	{
		final_path = ft_strjoin(data->paths[i], command);
		if (!final_path)
			return (NULL);
		if (access(final_path, X_OK) == 0)
		{
			free(command);
			return (final_path);
		}
		free(final_path);
	}
	return (NULL);
}

int	initialize_args(char **argv, t_list *data)
{
	data->output_args = ft_split(argv[3], ' ');
	if (!data->output_args)
		error("Output Arguments", data);
	data->output_command = data->output_args[0];
	data->input_args = ft_split(argv[3], ' ');
	if (!data->input_args)
		error("Input Arguments", data);
	data->input_command = data->input_args[0];
	return (0);
}
