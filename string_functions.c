/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:38:53 by stamim            #+#    #+#             */
/*   Updated: 2022/03/29 15:19:07 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strcmp(const char *const s1, const char *const s2)
{
	size_t	i;

	if (s1 != NULL && s2 != NULL)
	{
		i = 0;
		while (s1[i] != '\0' && s1[i] == s2[i])
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

size_t	ft_strlen(const char *const string);

size_t	ft_putstr_fd(const char *const string, const t_fd fd)
{
	return ((size_t) write(fd, string, ft_strlen(string) * sizeof(char)));
}

size_t	log_err(const char *const err)
{
	return (ft_putstr_fd(err, STDERR_FILENO)
		+ ft_putstr_fd("\n", STDERR_FILENO));
}

int	failure(const char *const err)
{
	perror(err);
	return (EXIT_FAILURE);
}
