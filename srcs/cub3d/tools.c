#include "../../incl/cub3d.h"

static void ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = 0;
}

void *ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

int mapWidth(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int mapHeight(char *s[])
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int search_map(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

void exit_if_null(void *p, char *message)
{
	if (!p)
	{
		perror(message);
		exit(EXIT_FAILURE);
	}
}
