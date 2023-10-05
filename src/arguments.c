/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:14:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/05 11:22:07 by abied-ch         ###   ########.fr       */
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

int	get_input_args(char **argv, t_list *data)
{
	char	**temp;
	int		i;
	int		size;

	size = 0;
	temp = ft_split(argv[2], ' ');
	if (!temp)
		return (-1);
	while (temp[size])
		size++;
	data->input_command = strdup(temp[0]);
	if (!data->input_command)
		return (ft_free_array(temp), -1);
	data->input_args = malloc((size + 1) * sizeof(char *));
	if (!data->input_args)
		return (ft_free_array(temp), free(data->input_command), -1);
	i = -1;
	while (++i < size - 1)
	{
		if (temp[i + 1])
			data->input_args[i] = ft_strdup(temp[i + 1]);
		if (!data->input_args[i] && !temp[i])
			return (ft_free_array(data->input_args),
				ft_free_array(temp), free(data->input_command), -1);
	}
	data->input_args[i] = argv[1];
	data->input_args[++i] = NULL;
	ft_free_array(temp);
	return (0);
}

int	get_output_args(char **argv, t_list *data)
{
	char	**temp;
	int		i;
	int		size;

	size = 0;
	temp = ft_split(argv[3], ' ');
	if (!temp)
		return (-1);
	while (temp[size])
		size++;
	data->output_command = strdup(temp[0]);
	if (!data->output_command)
		return (ft_free_array(temp), -1);
	data->output_args = malloc((size + 1) * sizeof(char *));
	if (!data->output_args)
		return (ft_free_array(temp), cleanup(data), -1);
	i = -1;
	while (++i < size - 1)
	{
		if (temp[i + 1])
			data->output_args[i] = ft_strdup(temp[i + 1]);
		if (!data->output_args[i] && !temp[i])
			return (cleanup(data), ft_free_array(temp), -1);
	}
	data->output_args[i] = argv[4];
	data->output_args[++i] = NULL;
	ft_free_array(temp);
	return (0);
}
