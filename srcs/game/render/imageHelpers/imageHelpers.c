/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageHelpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:17 by adouib            #+#    #+#             */
/*   Updated: 2022/11/05 23:26:29 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

/*color the pixel on the x, y coordinates*/
/*pixeloffset where the pixel laying down*/
void	coloring_pixel(t_game *game, int x, int y, unsigned int color)
{
	int		pixel_offset;
	char	*color_pixel;

	pixel_offset = (y * game->global_img->line_bytes) + \
		(x * (game->global_img->bpp / 8));
	color_pixel = game->global_img->frame_addr + pixel_offset;
	*(unsigned int *)color_pixel = color;
}

unsigned int	rgb_to_hex(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

// int	get_max(t_game *game) {
// 	int rows = map_height(game->parser->map);
// 	int *cols = ft_calloc(rows, sizeof(int *));
// 	int y = -1;
// 	while (++y < rows)
// 	{
// 		cols[y] = map_width(game->parser->map[y]);
// 	}

// 	 for (int i = 1; i < rows; ++i) {
// 		if (cols[0] < cols[i]) {
// 			cols[0] = cols[i];
// 		}
//   	}
// 	return cols[0];
// }


// char	**get_map(t_game *game)
// {
// 	char	**res;
// 	size_t	nbr_line;
// 	size_t	a;

// 	nbr_line = get_nbr_line(map, *i);
// 	res = malloc(sizeof(char *) * (nbr_line + 1));
// 	a = 0;
// 	while (a < nbr_line)
// 	{
// 		res[a] = get_line(map, i);
// 		a++;
// 	}
// 	res[a] = NULL;
// 	return (res);
// }

// int	map_width(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// int	map_height(char *s[])
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }
