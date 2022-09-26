/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/09/26 23:27:12 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_game *init(const char *av[])
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_if_null(game, "Allocation failed");
	game->map = map_read(av, game);
	if (!game->map)
		quit(NULL, "map is empty");
	game->mapWidthPx = mapWidth(game->map[0]); // map width length
	game->mapHeightPx = mapHeight(game->map); // map height length
	game->windowWidth = SQUARE_WIDTH * game->mapWidthPx;
	game->windowHeight = SQUARE_HEIGHT * game->mapHeightPx;
	game->halfWidth = game->windowWidth / 2;
	game->halfHeight = game->windowHeight / 2;
	game->movementSpeed = 10;
	game->rotation = 2;
	game->posX = game->windowWidth / 2; // init to the starting location on the map
	game->posY = game->windowHeight / 2;
	game->playerAngle = 90;
	game->fov = 60;													   // field of view of the player
	game->halfFov = game->fov / 2;									   // half of view of the player
	game->dirX = 0;													   // player starting rotation angle
	game->dirY = -1;												   // player starting rotattion angle
	game->rayAngleIncrement = ((double)game->fov / game->windowWidth); // fov / windowWidth

	return game;
}
