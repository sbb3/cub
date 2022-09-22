/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/09/22 08:07:57 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_game * init()
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_if_null(game, "Allocation failed");

	game->img_data = ft_calloc(1, sizeof(img_data));
	if (!game->img_data)
		exit_if_null(game->img_data, "Allocation failed");


	game->movementSpeed = 5;
	game->rotation = 5;

	game->posX = WINDOW_WIDTH / 2;
	game->posY = WINDOW_HEIGHT / 2;
	game->angle = 90;
	game->fov = 60;
	game->dirX = 0;
	game->dirY = -1;

	game->halfWidth = WINDOW_WIDTH / 2;
	game->halfHeight = WINDOW_HEIGHT / 2;

	return game;
}
