/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:51:55 by adouib            #+#    #+#             */
/*   Updated: 2022/10/15 20:43:16 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int scale_down(t_game *game, int minimap_size, int window_size, int coordinate)
{
	double scale_factor;

	scale_factor = (double)minimap_size / window_size;
	return (coordinate * scale_factor);
}

void edit_pixel(t_game *game, int startX, int startY, int sizeX, int sizeY, int color)
{
	int y = 0;
	int x;
	while (y < sizeY)
	{
		x = 0;
		while (x < sizeX)
		{
			coloring_pixel(game, x + startX, y + startY, color);
			x++;
		}
		y++;
	}
}

void drawLinePlayer(t_game *game, int startY, int startX, int color)
{
	// pythaghors equation
	int pixelsCount = 100;
	double pixelX = startX;
	double pixelY = startY;
	while (pixelsCount)
	{
		coloring_pixel(game, pixelX, pixelY, color);
		pixelX += game->pdir_x; // dirX = direction, default to 0, range  [ -1 < 0 < 1 ]
		pixelY -= game->pdir_y; // dirY = direction, default to -1, range [ -1 < 0 < 1 ]
		pixelsCount--;
	}
}

void draw_minimap_player(t_game *game)
{
	int player_pos_x_in_minimap;
	int player_pos_y_in_minimap;

	player_pos_x_in_minimap = scale_down(game, game->minimap_width, WINDOW_WIDTH, game->pos_x);
	player_pos_y_in_minimap = scale_down(game, game->minimap_height, WINDOW_HEIGHT, game->pos_y);
	// draw the player
	edit_pixel(game, player_pos_x_in_minimap, player_pos_y_in_minimap, 5, 5, 0xE4D00A);
	drawLinePlayer(game, player_pos_y_in_minimap, player_pos_x_in_minimap, 0xffffff);
}

void draw_minimap_walls(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				edit_pixel(game, x * MINIMAP_SIZE, y * MINIMAP_SIZE, MINIMAP_SIZE, MINIMAP_SIZE, 0x2da9d2);
			else
				edit_pixel(game, x * MINIMAP_SIZE, y * MINIMAP_SIZE, MINIMAP_SIZE, MINIMAP_SIZE, 0x1f2e2e);
			x++;
		}
		y++;
	}
}

void minimap(t_game *game)
{
	draw_minimap_walls(game);
	draw_minimap_player(game);
	edit_pixel(game, (WINDOW_WIDTH / 2) - 1, 0, 1, WINDOW_HEIGHT, 0x04FF0E);

	mlx_put_image_to_window(game->mlx, game->win, game->global_img->frame, 0, 0);
}
