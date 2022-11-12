/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:23:05 by labenall          #+#    #+#             */
/*   Updated: 2022/10/23 10:31:18 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

//hana kanjib content 
//awal 7aja kanskipi space 
//kangol hna ghansal7 l9adiya dyla kola contant yakon binathom new line
/*&& !is_sapce(map[*i + a])*/
char	*get_contet(char *map, size_t *i)
{
	char	*r;
	size_t	a;
	size_t	b;

	a = 0;
	while (is_sapce(map[*i]))
		(*i)++;
	while (map[*i + a] && map[*i + a] != '\n')
		a++;
	if (a == 0)
		exit_erreur("content not complete");
	r = malloc(sizeof(char) * (a + 1));
	b = 0;
	while (b < a)
	{
		r[b] = map[*i + b];
		b++;
	}
	r[b] = 0;
	(*i) += a;
	return (r);
}

//hana kanskip virgule ila kan g ola b machi r
void	skip_space_virgile(char *map, size_t *i, size_t b, size_t *a)
{
	int	virgule;

	virgule = 0;
	while (is_sapce(map[*i]))
		(*i)++;
	if (b > 0)
	{
		if (map[*i] == ',')
		{
			virgule = 1;
			(*i)++;
		}
		if (virgule == 0)
			exit_erreur("virgule entre numbers");
		while (is_sapce(map[*i]))
			(*i)++;
	}
	*a = 0;
	while (ft_isdigit(map[*i + *a]))
		(*a)++;
}

//get rgb color 
t_color	*get_content_color(char *map, size_t *i)
{
	t_color	*color;
	char	*nbr;
	size_t	a;
	size_t	b;

	b = 0;
	color = malloc(sizeof(t_color));
	color->color = NULL;
	while (b < 3)
	{
		skip_space_virgile(map, i, b, &a);
		nbr = get_number(map, i, a);
		if (b == 0)
			color->r = ft_atoi(nbr);
		else if (b == 1)
			color->g = ft_atoi(nbr);
		else if (b == 2)
			(color->b) = ft_atoi(nbr);
		(*i) += a;
		free(nbr);
		b++;
	}
	return (color);
}

//hna kanraja3 map 0o1oS kolha kan9ra okan7tha r res
char	**get_content_of_map(char *map, size_t *i)
{
	char	**res;
	size_t	nbr_line;
	size_t	a;

	ignore_first(map, i);
	nbr_line = get_nbr_line(map, *i);
	res = malloc(sizeof(char *) * (nbr_line + 1));
	a = 0;
	while (a < nbr_line)
	{
		res[a] = get_line(map, i);
		a++;
	}
	res[a] = NULL;
	return (res);
}

//hana kan9ra map kola b testture o coloer 
//bach na9ra kola wa7ad bo7do man ba3d
char	*get_map(size_t size, int fd)
{
	char	*map_char;
	char	c;
	size_t	i;

	map_char = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		read(fd, &c, 1);
		map_char[i] = c;
		i++;
	}
	map_char[i] = 0;
	return (map_char);
}
