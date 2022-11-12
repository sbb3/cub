/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:22:58 by labenall          #+#    #+#             */
/*   Updated: 2022/10/23 11:39:50 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

//hana kanjib number
char	*get_number(char *map, size_t *i, size_t a)
{
	char	*r;
	size_t	b;

	r = malloc(sizeof(char) * (a + 1));
	b = 0;
	while (b < a)
	{
		r[b] = map[*i + b];
		b++;
	}
	r[b] = 0;
	return (r);
}

// function katerja3 lina cha7al man charakter kayan f map li9rina
size_t	get_size_map(const char *name_map)
{
	size_t	size;
	int		fd;
	char	char_read;
	int		nbr_read;

	fd = open(name_map, O_RDONLY);
	size = 0;
	nbr_read = 1;
	while (nbr_read > 0)
	{
		nbr_read = read(fd, &char_read, 1);
		size++;
	}
	return (size);
}

//hana kan9ra cha7al man star kayan f map 
//ila kan chi star fih ghi new line o space kan7bas
size_t	get_nbr_line(char *map, size_t i)
{
	size_t	r;
	int		k;

	k = 0;
	r = 0;
	while (map[i])
	{
		if (!is_sapce(map[i]) && map[i] != '\n')
			k = 1;
		if (map[i] == '\n')
		{
			if (k == 1)
			{
				k = 0;
				r++;
			}
			else
				return (r);
		}
		i++;
	}
	return (cas_is_space_or_new_line(map, i, r, k));
}

//hna kanraja3 cha7al man caractere f star
int	get_nbr_char(char *map, int i)
{
	int	r;

	r = 0;
	while (map[i] && map[i] != '\n')
	{
		i++;
		r++;
	}
	return (r);
}

//hana kanraja3 line kamal
char	*get_line(char *map, size_t *i)
{
	char	*res;
	int		nbr_char;
	int		a;

	nbr_char = get_nbr_char(map, *i);
	res = malloc(sizeof(char) * (nbr_char + 1));
	a = 0;
	while (a < nbr_char)
	{
		res[a] = map[*i + a];
		a++;
	}
	res[a] = 0;
	*i += a + 1;
	return (res);
}
