/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/09/25 18:14:44 by adouib           ###   ########.fr       */
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

		// if (game->map[tmpY][tmpX] == '0')
		// {
			game->posX += game->dirX * game->movementSpeed;
			game->posY += game->dirY * game->movementSpeed;
		// }
	}
	if (keycode == S_KEY)
	{
		tmpY = (game->posY - game->dirY * game->movementSpeed) / SQUARE_HEIGHT;
		tmpX = (game->posX - game->dirX * game->movementSpeed) / SQUARE_WIDTH;

		// if (game->map[tmpY][tmpX] == '0')
		// {
			game->posX -= game->dirX * game->movementSpeed;
			game->posY -= game->dirY * game->movementSpeed;
		// }
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
	mlx_clear_window(game->mlx, game->win);
	drawWall(game);
	// drawRect(game, game->posY, game->posX, 10, 10, 0xcfc08);
	drawLinePlayer(game, game->posY, game->posX, 0xffffff);

	rayCasting(game);

	// printf("----------------\n");
	return (0);
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

	// drawWall(game);
	drawWall(game);
	drawLinePlayer(game, game->posY, game->posX, 0xffffff);
	// drawRect(game, game->posY, game->posX, 10, 10, 0xcfc08);
	rayCasting(game);

	mlx_loop_hook(game->mlx, render, game); // infinite loop -> drawing
	mlx_hook(game->win, 2, 0L, keyPressed, game);
	mlx_hook(game->win, 17, 0L, red_cross_quit, game);

	mlx_loop(game->mlx);
}
