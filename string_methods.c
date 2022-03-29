/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:05:51 by stamim            #+#    #+#             */
/*   Updated: 2022/03/28 20:51:49 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	ft_strlen(const char *const string)
{
	size_t	i;

	i = 0;
	if (string != NULL)
	{
		while (string[i] != '\0')
			i++;
	}
	return (i);
}

static void	ft_strcpy(const char *const src, char *dest)
{
	size_t	i;

	if (src != NULL && dest != NULL)
	{
		i = 0;
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
}

size_t	log_err(const char *const err);

char	*ft_strdup(const char *const string)
{
	char	*result;
	size_t	result_size;

	if (string != NULL)
	{
		result_size = ft_strlen(string);
		result = (char *)malloc(result_size + 1);
		if (result == NULL)
			log_err(MALLOC_FAILURE_MSG);
		else
		{
			ft_strcpy(string, result);
			return (result);
		}
	}
	return (NULL);
}

char	*ft_strnstr(const char *const haystack, const char *const needle,
						size_t len)
{
	size_t	i;
	size_t	cursor;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && len-- > 0)
	{
		cursor = 0;
		while (haystack[i] && haystack[i] == needle[cursor])
		{
			if (needle[++cursor] == 0)
				return ((char *)haystack + i - cursor + 1);
			i++;
		}
		len--;
		i -= cursor - 1;
	}
	return (NULL);
}

char	*ft_strjoin(char const *const s1, char const *const s2,
						const char *const seperator)
{
	char	*result;
	size_t	s1_size;
	size_t	result_size;
	size_t	seperator_size;

	if (s1 == NULL || s2 == NULL || seperator == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	seperator_size = ft_strlen(seperator);
	result_size = s1_size + seperator_size + ft_strlen(s2);
	result = (char *)malloc((result_size + 1) * sizeof(char));
	if (result == NULL)
		log_err(MALLOC_FAILURE_MSG);
	else
	{
		result[result_size] = '\0';
		ft_strcpy(s1, result);
		ft_strcpy(seperator, result + s1_size);
		ft_strcpy(s2, result + s1_size + seperator_size);
	}
	return (result);
}
