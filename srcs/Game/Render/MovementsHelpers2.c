/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MovementsHelpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:31:52 by adouib            #+#    #+#             */
/*   Updated: 2022/10/27 22:19:25 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

void	rotate_left(t_game *game)
{
	game->player_angle += ROTATION;
	correct_angle(&game->player_angle);
	game->pdir_x = cos(degree_to_radian(game->player_angle));
	game->pdir_y = sin(degree_to_radian(game->player_angle));
}

void	rotate_right(t_game *game)
{
	game->player_angle -= ROTATION;
	correct_angle(&game->player_angle);
	game->pdir_x = cos(degree_to_radian(game->player_angle));
	game->pdir_y = sin(degree_to_radian(game->player_angle));
}
