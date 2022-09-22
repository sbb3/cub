/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 09:02:07 by adouib            #+#    #+#             */
/*   Updated: 2022/09/16 15:20:53 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

char *ft_strdup(char *s)
{
	char *buf;
	int i;
	int j;
	int size;

	size = ft_strlen(s);
	buf = malloc(sizeof(char) * size + 1);
	if (!buf)
		return (0);
	i = 0;
	j = 0;
	while (s[j])
		buf[i++] = s[j++];
	buf[i] = '\0';
	return (buf);
}

char *ft_strjoin(char *backup, char *line)
{
	char *buf;
	int i;
	int j;
	int total_len;

	if (!backup)
		backup = ft_strdup("");
	total_len = ft_strlen(backup) + ft_strlen(line);
	buf = (char *)malloc(sizeof(char) * total_len + 1);
	if (!buf)
		return (0);
	i = 0;
	j = 0;
	while (backup[j])
		buf[i++] = backup[j++];
	j = 0;
	while (line[j])
		buf[i++] = line[j++];
	buf[i] = '\0';
	free(backup);
	free(line);
	return (buf);
}

int search_newline(char *s, char c)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *get_next_line(int fd)
{
	char *backup;
	char *line;
	char *c;
	int bytes_read;

	backup = NULL;
	bytes_read = 1;
	while (bytes_read > 0 && !search_newline(backup, '\n'))
	{
		c = malloc(2);
		if (!c)
			return (0);
		bytes_read = read(fd, c, BUFFER_SIZE);
		c[bytes_read] = '\0';
		backup = ft_strjoin(backup, c);
	}
	if (*backup == '\0')
	{
		free(backup);
		return (0);
	}
	line = ft_strdup(backup);
	free(backup);
	return (line);
}
