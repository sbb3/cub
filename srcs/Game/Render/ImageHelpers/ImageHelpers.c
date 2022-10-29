/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageHelpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:17 by adouib            #+#    #+#             */
/*   Updated: 2022/10/29 15:43:34 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	edit_pixel(t_game *game, int startX, int startY, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_SIZE)
			coloring_pixel(game, x + startX, y + startY, color);
	}
}

/*color the pixel on the x, y coordinates*/
/*pixeloffset where the pixel laying down*/
void	coloring_pixel(t_game *game, int x, int y, int color)
{
	int		pixel_offset;
	char	*color_pixel;

	pixel_offset = (y * game->global_img->line_bytes) + \
		(x * (game->global_img->bpp / 8));
	color_pixel = game->global_img->frame_addr + pixel_offset;
	*(unsigned int *)color_pixel = color;
}
