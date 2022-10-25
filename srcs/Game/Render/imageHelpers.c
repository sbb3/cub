/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageHelpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:17 by adouib            #+#    #+#             */
/*   Updated: 2022/10/25 16:40:32 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

/* global image freeing */
void	delete_global_image_then_clear_window(t_game *game)
{
	if (game->global_img->frame)
		mlx_destroy_image(game->mlx, game->global_img->frame);
	mlx_clear_window(game->mlx, game->win);
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
