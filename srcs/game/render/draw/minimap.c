/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:51:55 by adouib            #+#    #+#             */
/*   Updated: 2022/11/05 19:33:09 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

int	scale_down(int minimap_size, int window_size, int coordinate)
{
	double	scale_factor;

	scale_factor = (double)minimap_size / window_size;
	return (coordinate * scale_factor);
}

void	draw_arrow_line(t_game *game, int start_x, int start_y, float new_angle)
{
	int		pixels_count;
	double	pixel_x;
	double	pixel_y;

	pixels_count = 10;
	pixel_x = start_x;
	pixel_y = start_y;
	while (pixels_count)
	{
		coloring_pixel(game, pixel_x, pixel_y, 0xff0000);
		pixel_x += cos(deg_2_rad(new_angle));
		pixel_y -= sin(deg_2_rad(new_angle));
		pixels_count--;
	}
}

/*
draw right arrow line => game->player_angle - 140
draw left arrow line => game->player_angle + 140
*/
void	draw_minimap_arrow(t_game *game)
{
	int		scaled_pos_x;
	int		scaled_pos_y;
	float	right_arrow_angle;
	float	left_arrow_angle;

	scaled_pos_x = scale_down(game->minimap_width, WINDOW_WIDTH, \
		game->pos_x);
	scaled_pos_y = scale_down(game->minimap_height, WINDOW_HEIGHT, \
		game->pos_y);
	right_arrow_angle = (game->player_angle - 140);
	correct_angle(&right_arrow_angle);
	draw_arrow_line(game, scaled_pos_x, scaled_pos_y, right_arrow_angle);
	left_arrow_angle = (game->player_angle + 140);
	correct_angle(&left_arrow_angle);
	draw_arrow_line(game, scaled_pos_x, scaled_pos_y, left_arrow_angle);
}

void	draw_minimap_walls(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				edit_pixel(game, x * MINIMAP_SIZE, y * MINIMAP_SIZE, 0x000000);
			else
				edit_pixel(game, x * MINIMAP_SIZE - 1, y * MINIMAP_SIZE - 1, 0xffffff);
			x++;
		}
		y++;
	}
}

void	minimap(t_game *game)
{
	draw_minimap_walls(game);
	draw_minimap_arrow(game);
	mlx_put_image_to_window(game->mlx, game->win, game->global_img->frame, \
		0, 0);
}
