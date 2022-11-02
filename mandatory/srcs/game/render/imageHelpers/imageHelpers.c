/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageHelpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:17 by adouib            #+#    #+#             */
/*   Updated: 2022/11/02 21:22:43 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

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

unsigned int	rgb_to_hex(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}
