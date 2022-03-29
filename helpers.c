/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:04:23 by stamim            #+#    #+#             */
/*   Updated: 2022/03/29 01:09:27 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_arr_string(char **arr)
{
	size_t	i;

	if (arr != NULL)
	{
		i = 0;
		while (arr[i] != NULL)
		{
			free((void *)arr[i]);
			arr[i] = NULL;
			i++;
		}
	}
}

void	free_arr_int(t_fd **arr, size_t end)
{
	size_t	i;

	if (arr != NULL)
	{
		i = 0;
		while (i < end)
		{
			free((void *)arr[i]);
			arr[i] = NULL;
			i++;
		}
	}
}

char	*get_full_path(char *paths[], const char *const command)
{
	size_t	i;
	char	*full_path;

	if (paths != NULL)
	{
		i = 0;
		while (paths[i] != NULL)
		{
			full_path = ft_strjoin(paths[i], command, "/");
			if (access(full_path, F_OK) == 0)
				return (full_path);
			full_path = (free((void *)full_path), NULL);
			i++;
		}
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		log_err(COMMAND_NOT_FOUND);
	}
	return (NULL);
}

int	write_to_child(char *line, t_fd write_end)
{
	return (
		ft_putstr_fd(line, write_end) + ft_putstr_fd("\n", write_end));
}
