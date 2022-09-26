/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/09/26 22:00:07 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int keyPressed(int keycode, t_game *game)
{
	int tmpY = 0;
	int tmpX = 0;
	if (keycode == ESC_KEY)
		quit(game, NULL);
	if (keycode == W_KEY)
	{
		tmpY = (game->posY + game->dirY * game->movementSpeed) / SQUARE_HEIGHT;
		tmpX = (game->posX + game->dirX * game->movementSpeed) / SQUARE_WIDTH;

		if (game->map[tmpY][tmpX] == '0')
		{
			game->posX += game->dirX * game->movementSpeed;
			game->posY += game->dirY * game->movementSpeed;
		}
	}
	if (keycode == S_KEY)
	{
		tmpY = (game->posY - game->dirY * game->movementSpeed) / SQUARE_HEIGHT;
		tmpX = (game->posX - game->dirX * game->movementSpeed) / SQUARE_WIDTH;

		if (game->map[tmpY][tmpX] == '0')
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
		game->rotationAngle += game->rotation;
		game->dirX = cos(degreeToRadian(game->rotationAngle));
		game->dirY = -sin(degreeToRadian(game->rotationAngle));

		game->rotationAngle = game->rotationAngle % 360;
		if (game->rotationAngle < 0)
			game->rotationAngle = 360 + game->rotationAngle;
	}
	if (keycode == RIGHT_KEY)
	{
		game->rotationAngle -= game->rotation;
		game->dirX = cos(degreeToRadian(game->rotationAngle));
		game->dirY = -sin(degreeToRadian(game->rotationAngle));

		game->rotationAngle = game->rotationAngle % 360;
		if (game->rotationAngle < 0)
			game->rotationAngle = 360 + game->rotationAngle;
	}
	free_image(game);
	mlx_clear_window(game->mlx, game->win);
	game->imgData = createImage(game); //!!!!
	drawWall(game);
	// drawLinePlayer(game, game->posY, game->posX, 0xffffff); //!!! remove this
	rayCasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->imgData->frame, 0, 0); //!!!!
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

void drawWall(t_game *game)
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

void drawLinePlayer(t_game *game, int startY, int startX, int color)
{
	// pythaghors equation
	int pixelsCount = 350;
	double pixelX = startX;
	double pixelY = startY;

	while (pixelsCount)
	{
		edit_pixel(game->imgData->frame_addr, game->imgData->sLine, game->imgData->bpp, pixelX, pixelY, color);

		pixelX += game->dirX; // dirX = direction, default to 0, range  [ -1 < 0 < 1 ]
		pixelY += game->dirY; // dirY = direction, default to -1, range [ -1 < 0 < 1 ]
		pixelsCount--;
	}
}


int main(int ac, const char *av[])
{
	t_game *game;

	if (ac != 2)
		quit(NULL, "Format: ./cub3d <map name>.cub");

	game = init(av);
	parser(av, game);

	game->mlx = mlx_init();
	if (!game->mlx)
		quit(game, "Connection to the X-Window Server failed");
	game->win = mlx_new_window(game->mlx, game->WINDOW_WIDTH, game->WINDOW_HEIGHT, "CUB3D");
	if (!game->win)
		quit(game, "New window initialization failed");

	// printf("%d\n", game->WINDOW_WIDTH);

	game->imgData = createImage(game); //!!!!
	drawWall(game);
	// drawLinePlayer(game, game->posY, game->posX, 0xffffff); //!!! remove this
	rayCasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->imgData->frame, 0, 0); //!!!!

	// mlx_loop_hook(game->mlx, render, game); // infinite loop -> drawing
	mlx_hook(game->win, 2, 0L, keyPressed, game);
	mlx_hook(game->win, 17, 0L, red_cross_quit, game);

	mlx_loop(game->mlx);
}
