/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/09/23 09:14:41 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_game * init(const char *av[])
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_if_null(game, "Allocation failed");

	game->img_data = ft_calloc(1, sizeof(img_data));
	if (!game->img_data)
		exit_if_null(game->img_data, "Allocation failed");

	game->map = map_read(av, game);
	if (!game->map)
		quit(NULL, "map is empty");
	game->map_width = map_width(game->map[0]);
	game->map_height = map_height(game->map);

	game->WINDOW_WIDTH = IMG_WIDTH * game->map_width;
	game->WINDOW_HEIGHT = IMG_HEIGHT * game->map_height;

	game->movementSpeed = 0.3;
	game->rotation = 2;

	game->posX = game->WINDOW_WIDTH / 2;
	game->posY = game->WINDOW_HEIGHT / 2;
	game->angle = 90;
	game->fov = 60; // field of view
	game->dirX = 0;
	game->dirY = -1;

	game->halfWidth = game->WINDOW_WIDTH / 2;
	game->halfHeight = game->WINDOW_HEIGHT / 2;

	return game;
}
