/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:14:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/06 19:14:07 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parse_environment(char **envp, t_dumpster *data)
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
			{
				cleanup(data);
				exit(EXIT_FAILURE);
			}
		}
		envp++;
	}
	envp = temp;
	return (0);
}

char	*get_path(char *command, t_dumpster *data)
{
	int		i;
	char	*final_path;

	if (!data->paths)
		return (NULL);
	if (access(command, R_OK | X_OK) == 0)
		return (command);
	i = -1;
	command = ft_strjoin("/", command);
	if (!command)
		return (perror("💀 memory allocation 💀"), NULL);
	while (data->paths[++i])
	{
		final_path = ft_strjoin(data->paths[i], command);
		if (!final_path)
			return (perror("💀 memory allocation 💀"), free(command), NULL);
		if (access(final_path, R_OK | X_OK) == 0)
			return (free(command), final_path);
		free(final_path);
	}
	perror("💀 command not found 💀");
	free(command);
	return (NULL);
}

int	initialize_args(char **argv, t_dumpster *data)
{
	data->output_args = ft_split(argv[3], ' ');
	if (!data->output_args)
	{
		perror("💀 output arguments 💀");
		cleanup(data);
		exit (-1);
	}
	data->output_command = data->output_args[0];
	data->input_args = ft_split(argv[2], ' ');
	if (!data->input_args)
	{
		perror("💀 input arguments 💀");
		cleanup(data);
		exit (-1);
	}
	data->input_command = data->input_args[0];
	return (0);
}
