/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getSetColors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:40:25 by adouib            #+#    #+#             */
/*   Updated: 2022/11/03 10:37:57 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

unsigned int	get_the_color_from_north_texture(t_game *game)
{
	int		pixel_offset;
	char	*color_pixel;

	pixel_offset = (game->texture_offset_y * game->n_t_data->line_bytes) + \
		(game->texture_offset_x * (game->n_t_data->bpp / 8));
	color_pixel = game->n_t_data->frame_addr + pixel_offset;
	return (*(unsigned int *)color_pixel);
}

unsigned int	get_the_color_from_south_texture(t_game *game)
{
	int		pixel_offset;
	char	*color_pixel;

	pixel_offset = (game->texture_offset_y * game->s_t_data->line_bytes) + \
		(game->texture_offset_x * (game->s_t_data->bpp / 8));
	color_pixel = game->s_t_data->frame_addr + pixel_offset;
	return (*(unsigned int *)color_pixel);
}

unsigned int	get_the_color_from_west_texture(t_game *game)
{
	int		pixel_offset;
	char	*color_pixel;

	pixel_offset = (game->texture_offset_y * game->w_t_data->line_bytes) + \
		(game->texture_offset_x * (game->w_t_data->bpp / 8));
	color_pixel = game->w_t_data->frame_addr + pixel_offset;
	return (*(unsigned int *)color_pixel);
}

unsigned int	get_the_color_from_east_texture(t_game *game)
{
	int		pixel_offset;
	char	*color_pixel;

	pixel_offset = (game->texture_offset_y * game->e_t_data->line_bytes) + \
		(game->texture_offset_x * (game->e_t_data->bpp / 8));
	color_pixel = game->e_t_data->frame_addr + pixel_offset;
	return (*(unsigned int *)color_pixel);
}

void	set_the_texture_color_on_walls(t_game *game, int x, int y, \
	unsigned int color)
{
	int		pixel_offset;
	char	*color_pixel;

	pixel_offset = (y * game->global_img->line_bytes) \
		+ (x * game->global_img->bpp / 8);
	color_pixel = game->global_img->frame_addr + pixel_offset;
	*(unsigned int *)color_pixel = color;
}
