/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autre_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:22:34 by labenall          #+#    #+#             */
/*   Updated: 2022/10/23 10:31:18 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	is_player(char c)
{
	if (c == 'E' || c == 'N' || c == 'S' || c == 'W')
		return (1);
	else
		return (0);
}

int	is_char_map(char c)
{
	if (c == '1' || c == '0' || is_player(c) || c == ' ')
		return (1);
	else
		return (0);
}

//hna kanchof les texture wach kaysaliw b xpm
void	cheak_texure(t_map *map_struct)
{
	if (cheak_name_texure(map_struct->ea->path) == 1)
		exit_erreur("texure eo must finish by .xpm");
	if (cheak_name_texure(map_struct->we->path) == 1)
		exit_erreur("texure we must finish by .xpm");
	if (cheak_name_texure(map_struct->no->path) == 1)
		exit_erreur("texure no must finish by .xpm");
	if (cheak_name_texure(map_struct->so->path) == 1)
		exit_erreur("texure so must finish by .xpm");
}

//han kanjib height o width dyal map kan7thom f struct 
void	initial_h_w(t_map *map_struct)
{
	int	width;
	int	height;
	int	i;
	int	j;

	width = 0;
	height = 0;
	i = 0;
	while (map_struct->map[i])
	{
		j = 0;
		while (map_struct->map[i][j])
			j++;
		if (j > width)
			width = j;
		i++;
	}
	height = i;
	map_struct->height = height + 1;
	map_struct->width = width + 1;
}
