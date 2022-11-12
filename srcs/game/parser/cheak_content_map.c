/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheak_content_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:52:32 by labenall          #+#    #+#             */
/*   Updated: 2022/10/29 11:49:18 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

//hna kaydkhal liha f 7alat ghayjib texture 
void	cas_stel2(t_map *map, char *type, int *nbr_type, size_t *i)
{
	if (ft_strcmp(type, "NO") == 0)
	{
		map->no = add_content(map, i);
	}
	else if (ft_strcmp(type, "SO") == 0)
	{
		map->so = add_content(map, i);
	}
	else if (ft_strcmp(type, "WE") == 0)
	{
		map->we = add_content(map, i);
	}
	else if (ft_strcmp(type, "EA") == 0)
	{
		map->ea = add_content(map, i);
	}
	else
		exit_erreur("erreur 2 caractere in map");
	(*nbr_type)++;
}

//hna kaydkhal liha f7alat ghayjib color 
void	cas_strlen1(t_map *map, char *type, int *nbr_type, size_t *i)
{
	if (ft_strcmp(type, "F") == 0)
		map->f = get_content_color(map->all_map, i);
	else if (ft_strcmp(type, "C") == 0)
		map->c = get_content_color(map->all_map, i);
	else
		exit_erreur("erreur 1 caractere in map");
	(*nbr_type)++;
}

//ila kan chi player ola 0 fo9o ola ta7to ola janbo lkhwa
void	cheak_incorecte_space(t_map *map_struct, size_t a, int b)
{
	if (b == 0)
		exit_erreur("0 or player in begin of line");
	if (b >= ft_strlen(map_struct->map[a - 1]) || \
	b >= ft_strlen(map_struct->map[a + 1]))
		exit_erreur("0 or player in line big then other");
	if (is_sapce(map_struct->map[a - 1][b]))
		exit_erreur("up 0 or player is space");
	if (is_sapce(map_struct->map[a][b + 1]))
		exit_erreur("after 0 or player is space");
	if (is_sapce(map_struct->map[a][b - 1]))
		exit_erreur("before 0 or player is space");
	if (is_sapce(map_struct->map[a + 1][b]))
		exit_erreur("down 0 or player is space");
}

//ila kan chi caractere makhsoch ikon ola ila 
//kan ktar man player ila kan player 
void	cheak_caractere(t_map *map_struct, size_t a, size_t b, int *p)
{
	if (!is_char_map(map_struct->map[a][b]))
		exit_erreur("wrong char in map");
	if (is_player(map_struct->map[a][b]))
	{
		if (*p == 0)
		{
			map_struct->p_direction = map_struct->map[a][b];
			map_struct->xp = a;
			map_struct->yp = b;
		}
		else
			exit_erreur("only one player");
		*p = 1;
	}
	if (a == 0 && (map_struct->map[a][b] == '0' || \
	is_player(map_struct->map[a][b])))
		exit_erreur("Wall not Complete in begin");
	if (!map_struct->map[a + 1] && (map_struct->map[a][b] == '0' || \
	is_player(map_struct->map[a][b])))
		exit_erreur("Wall not complete in end");
	if (!map_struct->map[a][b + 1] && (map_struct->map[a][b] == '0' || \
	is_player(map_struct->map[a][b])))
		exit_erreur("Wall not complete in end");
	if (map_struct->map[a][b] == '0' || is_player(map_struct->map[a][b]))
		cheak_incorecte_space(map_struct, a, b);
}

//hna kanchof wach texture kaynin o kanchiki map o wach kayan player
void	cheak_content_map(t_map *map_struct)
{
	size_t	a;
	size_t	b;
	int		p;

	a = 0;
	p = 0;
	cheak_texure(map_struct);
	while (map_struct->map[a])
	{
		b = 0;
		while (map_struct->map[a][b])
		{
			cheak_caractere(map_struct, a, b, &p);
			b++;
		}
		a++;
	}
	if (map_struct->p_direction == 0)
		exit_erreur("Player not exist in map");
	initial_h_w(map_struct);
}
