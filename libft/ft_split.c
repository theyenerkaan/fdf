/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:23:10 by yenyilma          #+#    #+#             */
/*   Updated: 2024/12/18 05:39:36 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*delete(char **s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(s[i]);
		i++;
	}
	free (s);
	return (NULL);
}

static int	counter(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*word_filler(const char *s, char c)
{
	int			letter_count;
	int			i;
	char		*string;
	const char	*copied;

	i = 0;
	letter_count = 0;
	copied = s;
	while (*s != c && *s)
	{
		letter_count++;
		s++;
	}
	string = (char *) malloc (sizeof(char) * (letter_count + 1));
	if (!string)
		return (NULL);
	while (i < letter_count)
	{
		string[i++] = *copied++;
	}
	string[i] = 0;
	return (string);
}

char	**ft_split(char const *s, char c)
{
	char		**strings;
	int			i;
	int			word_count;

	i = 0;
	word_count = counter(s, c);
	strings = (char **) malloc (sizeof(char *) * (word_count + 1));
	if (!strings)
		return (NULL);
	while (i < word_count)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			strings[i] = word_filler(s, c);
			if (!strings[i])
				return (delete (strings, i));
			while (*s && *s != c)
				s++;
		}
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
