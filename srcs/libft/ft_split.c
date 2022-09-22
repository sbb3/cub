/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:13:46 by adouib            #+#    #+#             */
/*   Updated: 2022/01/03 12:13:47 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_map(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	k;
	int	words;

	i = 0;
	words = 0;
	k = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			k = 1;
			i++;
		}
		else if (s[i] != c && k == 1)
		{
			words++;
			k = 0;
			i++;
		}
		else
			i++;
	}
	return (words);
}

static char	*ft_strcut_from_to(char const *s, int from, int to)
{
	char	*buf;
	int		i;

	buf = (char *)malloc(sizeof(char) * (to - from) + 1);
	if (!buf)
		return (NULL);
	i = 0;
	while (from < to)
	{
		buf[i] = s[from];
		from++;
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

static char	**words_slice(char const *s, char c, char **token, int wc)
{
	int	i;
	int	start;
	int	end;

	start = 0;
	i = 0;
	while (i < wc)
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		token[i] = ft_strcut_from_to(s, start, end);
		if (!token)
			return (free_map(token));
		start = end;
		i++;
	}
	token[i] = NULL;
	return (token);
}

char	**ft_split(char *s, char c)
{
	char	**token;
	int		wc;

	if (s == NULL)
		return (NULL);
	wc = word_count(s, c);
	token = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!token)
		return (NULL);
	token = words_slice(s, c, token, wc);
	free(s);
	return (token);
}
