/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/09/26 23:43:45 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int keyPressed(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		quit(game, NULL);
	if (keycode == W_KEY)
	{
		if (game->map[(int)((game->posY + game->dirY * game->movementSpeed) / SQUARE_HEIGHT)]
			[(int)((game->posX + game->dirX * game->movementSpeed) / SQUARE_WIDTH)] == '0')
		{
			game->posX += game->dirX * game->movementSpeed;
			game->posY += game->dirY * game->movementSpeed;
		}
	}
	if (keycode == S_KEY)
	{
		if (game->map[(int)((game->posY - game->dirY * game->movementSpeed) / SQUARE_HEIGHT)]
			[(int)((game->posX - game->dirX * game->movementSpeed) / SQUARE_WIDTH)] == '0')
		{
			game->posX -= game->dirX * game->movementSpeed;
			game->posY -= game->dirY * game->movementSpeed;
		}
	}
	if (keycode == A_KEY)
	{
		game->posX = game->posX - game->rotation;
	}
	if (keycode == D_KEY)
	{
		game->posX = game->posX + game->rotation;
	}
	if (keycode == LEFT_KEY)
	{
		game->playerAngle += game->rotation;
		game->dirX = cos(degreeToRadian(game->playerAngle));
		game->dirY = -sin(degreeToRadian(game->playerAngle));

		game->playerAngle = game->playerAngle % 360;
		if (game->playerAngle < 0)
			game->playerAngle = 360 + game->playerAngle;
	}
	if (keycode == RIGHT_KEY)
	{
		game->playerAngle -= game->rotation;
		game->dirX = cos(degreeToRadian(game->playerAngle));
		game->dirY = -sin(degreeToRadian(game->playerAngle));

		game->playerAngle = game->playerAngle % 360;
		if (game->playerAngle < 0)
			game->playerAngle = 360 + game->playerAngle;
	}
	// fix the above part
	deleteImage(game);
	mlx_clear_window(game->mlx, game->win);
	game->imgData = createImage(game); //!!!!
	draw(game); // !! will get removed and used the render function
	return (0);
}

void drawRect(t_game *game, int startY, int startX, int sizeY, int sizeX, int color)
{
	int y = 0;
	int x;
	while (y < sizeY)
	{
		x = 0;
		while (x < sizeX)
		{
			edit_pixel(game->imgData->frame_addr, game->imgData->sLine, game->imgData->bpp, x + startX, y + startY, color);
			x++;
		}
		y++;
	}
}

void drawWalls(t_game *game)
{
	int y = 0;
	int x;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				drawRect(game, y * SQUARE_SIZE, x * SQUARE_SIZE, SQUARE_SIZE - 1, SQUARE_SIZE - 1, 0x2da9d2);
			else

				drawRect(game, y * SQUARE_SIZE, x * SQUARE_SIZE, SQUARE_SIZE - 1, SQUARE_SIZE - 1, 0x1f2e2e);
			x++;
		}
		y++;
	}
}

void mlxInit(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		quit(game, "Connection to the X-Window Server failed");
	game->win = mlx_new_window(game->mlx, game->windowWidth, game->windowHeight, "CUB3D");
	if (!game->win)
		quit(game, "New window initialization failed");
	game->imgData = createImage(game);
}

void draw(t_game *game)
{
	drawWalls(game);
	rayCasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->imgData->frame, 0, 0);
}

int main(int ac, const char *av[])
{
	t_game *game;

	if (ac != 2)
		quit(NULL, "Format: ./cub3d <map name>.cub");
	game = init(av);
	// parser(av, game);
	mlxInit(game);
	draw(game); // !! will get removed and used the render function
	// mlx_loop_hook(game->mlx, render, game); // infinite loop -> drawing
	mlx_hook(game->win, 2, 0L, keyPressed, game);
	mlx_hook(game->win, 17, 0L, red_cross_quit, game);
	mlx_loop(game->mlx);
}
