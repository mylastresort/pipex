/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:43:08 by stamim            #+#    #+#             */
/*   Updated: 2022/03/28 20:51:38 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	**malloc_crash(char **p, size_t i)
{
	while (i--)
		free(p[i]);
	free(p);
	return (NULL);
}

static int	get_words_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] == 0)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		count++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static void	copy_word(char *p, char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = 0;
}

static char	**push_strings(char const *s, char c, size_t n, char **p)
{
	size_t	i;
	size_t	count;
	size_t	size;

	i = 0;
	count = 0;
	while (s[count] && s[count] == c)
		count++;
	while (n > i)
	{
		size = 0;
		while (s[size + count] && s[size + count] != c)
			size++;
		p[i] = (char *)malloc(sizeof(char) * (size + 1));
		if (p[i] == NULL)
			return (malloc_crash(p, i));
		copy_word(p[i], (char *)s + count, c);
		count += size;
		while (s[count] && s[count] != c)
			count++;
		while (s[count] && s[count] == c)
			count++;
		i++;
	}
	return (p);
}

char	**ft_split(char const *s, const char c)
{
	size_t	n;
	char	**p;

	if (s == NULL)
		return (NULL);
	n = (size_t)get_words_count(s, c);
	p = (char **)malloc(sizeof(char *) * (n + 1));
	if (p == NULL)
		return (NULL);
	p[n] = NULL;
	if (s[0] != 0)
		return (push_strings(s, c, n, p));
	return (p);
}
