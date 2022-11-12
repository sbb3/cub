/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_cas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:23:20 by labenall          #+#    #+#             */
/*   Updated: 2022/10/23 10:31:18 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

//kancopie content se ola b7alha
char	*ft_copier(char *s, size_t size)
{
	char	*r;
	size_t	i;

	i = 0;
	r = malloc(sizeof(char) * (size + 1));
	while (i < size)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = 0;
	return (r);
}

//ila kan chi space ola new line kanskipihom f lawal
void	ignore_first(char *map, size_t *i)
{
	size_t	a;

	while (map[*i])
	{
		a = 0;
		while (map[*i + a] == '\n')
			(*i)++;
		while (is_sapce(map[*i + a]))
			a++;
		if (map[*i + a] == '\n')
		{
			*i += a + 1;
		}
		else if (map[*i + a] != '\0')
		{
			break ;
		}
		else
			exit_erreur("incomplete map");
	}
}

t_type	*add_content(t_map *map, size_t *i)
{
	t_type	*type;

	type = malloc(sizeof(t_type));
	type->path = NULL;
	type->path = get_contet(map->all_map, i);
	return (type);
}

size_t	cas_is_space_or_new_line(char *map, size_t i, size_t r, int k)
{
	if (map[i] == 0)
	{
		if (k == 1)
			return (r + 1);
		else
			return (r);
	}
	else
		return (r);
}
