/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheak.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:22:41 by labenall          #+#    #+#             */
/*   Updated: 2022/11/02 21:11:43 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

//cheak smaya wach katsali b .cub
int	cheak_name(const char *name)
{
	size_t	size;

	size = ft_strlen(name);
	if (ft_strcmp((name + size - 4), ".cub") != 0)
		return (1);
	else
		return (0);
}

//cheak wach smya dyal texture katsali b .xpm
int	cheak_name_texure(char *name)
{
	size_t	size;

	size = ft_strlen(name);
	if (ft_strcmp((name + size - 4), ".xpm") != 0)
		return (1);
	else
		return (0);
}

//kanchof wach texture o color kamlin kaynin 
void	cheak_type(t_map *map_struct)
{
	if (map_struct->c == NULL)
		exit_erreur("C not exit in map");
	if (map_struct->f == NULL)
		exit_erreur("F not exit in map");
	if (map_struct->ea == NULL)
		exit_erreur("EA not exit in map");
	if (map_struct->no == NULL)
		exit_erreur("NO not exist in map");
	if (map_struct->so == NULL)
		exit_erreur("SO not exist in map");
	if (map_struct->we == NULL)
		exit_erreur("WE not exist in map");
	map_struct->c->color = encodec_color(map_struct->c->r, \
	map_struct->c->g, map_struct->c->b);
	map_struct->f->color = encodec_color(map_struct->f->r, \
	map_struct->f->g, map_struct->f->b);
}

//skip space o new line 
//kaninitializi j b 0 bach n7asab cha7a ghancopie man map wach 2 ola 1
//man ba3daha kanskipi space 
void	cheak_and_get_type(t_map *map, size_t *i, size_t *j, int *nbr_type)
{
	char	*type;

	while (map->all_map[*i] && (is_sapce(map->all_map[*i]) || \
	map->all_map[*i] == '\n'))
		(*i)++;
	*j = 0;
	while (map->all_map[*i + *j] && !is_sapce(map->all_map[*i + *j]) && \
	map->all_map[*i + *j] != '\n')
		(*j)++;
	type = ft_copier(map->all_map + *i, *j);
	*i += *j;
	if (ft_strlen(type) == 2)
		cas_stel2(map, type, nbr_type, i);
	else if (ft_strlen(type) == 1)
		cas_strlen1(map, type, nbr_type, i);
	else
		exit_erreur("map non complete");
	while (map->all_map[*i] && is_sapce(map->all_map[*i]))
		(*i)++;
	free(type);
	if (map->all_map[*i] == 0)
		exit_erreur("incopmlete map");
}

//hanya kanjib 6 dyal type 3AD kandoz njib map
//ila kant chi 7aja man wara map rah erreur 
void	cheak_map(t_map *map)
{
	size_t	i;
	size_t	j;
	int		nbr_type;

	i = 0;
	nbr_type = 0;
	while (map->all_map[i] && nbr_type < 6)
	{
		cheak_and_get_type(map, &i, &j, &nbr_type);
		if (map->all_map[i] != 10)
			exit_erreur("must new line after content");
	}
	map->map = get_content_of_map(map->all_map, &i);
	while (map->all_map[i])
	{
		if (map->all_map[i] && !is_sapce(map->all_map[i]) && \
		map->all_map[i] != '\n')
			exit_erreur("in map after get content of map");
		i++;
	}
}
