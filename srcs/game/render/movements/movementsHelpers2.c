/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movementsHelpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:31:52 by adouib            #+#    #+#             */
/*   Updated: 2022/11/09 11:43:34 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

/* ROTATION_SPEED : how MANY angles per frame I increase or decrease */
void	rotate_left(t_game *game)
{
	game->player_angle += ROTATION_SPEED;
	correct_angle(&game->player_angle);
	game->pdir_x = cos(deg_2_rad(game->player_angle));
	game->pdir_y = sin(deg_2_rad(game->player_angle));
}

void	rotate_right(t_game *game)
{
	game->player_angle -= ROTATION_SPEED;
	correct_angle(&game->player_angle);
	game->pdir_x = cos(deg_2_rad(game->player_angle));
	game->pdir_y = sin(deg_2_rad(game->player_angle));
}
