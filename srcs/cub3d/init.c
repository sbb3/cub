/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/09/25 22:47:58 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_game *init(const char *av[])
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_if_null(game, "Allocation failed");

	// game->imgData = ft_calloc(1, sizeof(game->imgData));
	// if (!game->imgData)
	// 	exit_if_null(game->imgData, "Allocation failed");

	game->map = map_read(av, game);
	if (!game->map)
		quit(NULL, "map is empty");
	game->map_width = map_width(game->map[0]);
	game->map_height = map_height(game->map);

	game->WINDOW_WIDTH = SQUARE_WIDTH * game->map_width;
	game->WINDOW_HEIGHT = SQUARE_HEIGHT * game->map_height;

	game->movementSpeed = 5;
	game->rotation = 2;

	game->posX = game->WINDOW_WIDTH / 2;
	game->posY = game->WINDOW_HEIGHT / 2;
	game->rotationAngle = 90;
	game->fov = 60; // field of view
	game->halfFov = game->fov / 2;
	game->dirX = 0;	 // player starting rotation angle
	game->dirY = -1; // player starting rotattion angle

	game->halfWidth = game->WINDOW_WIDTH / 2;
	game->halfHeight = game->WINDOW_HEIGHT / 2;

	game->rayUp = 0;
	game->rayDown = 0;
	game->rayLeft = 0;
	game->rayRight = 0;
	game->rayAngleIncrem = (double) game->fov / (double) game->WINDOW_WIDTH;

	// game->rayAngle = 0.00;
	// game->rayAngleY = 0;
	// game->rayAngleX = 0;
	return game;
}
