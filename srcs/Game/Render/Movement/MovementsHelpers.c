/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MovementsHelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:31:52 by adouib            #+#    #+#             */
/*   Updated: 2022/11/01 21:13:26 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	move_up(t_game *game)
{
	if (((!is_wall_on_up(game) && !is_wall_on_left(game, 45)) \
		&& (!is_wall_on_up(game) && !is_wall_on_left(game, 90))) \
		|| ((!is_wall_on_up(game) && !is_wall_on_right(game, 45)) \
		&& (!is_wall_on_up(game) && !is_wall_on_right(game, 90))))
	{
		game->pos_y -= game->pdir_y * SPEED;
		game->pos_x += game->pdir_x * SPEED;
	}
}

void	move_down(t_game *game)
{
	int	next_move_y;
	int	next_move_x;

	next_move_y = (game->pos_y + game->pdir_y * SPEED) / SQUARE_HEIGHT;
	next_move_x = (game->pos_x - game->pdir_x * SPEED) / SQUARE_WIDTH;
	if (((!is_wall_on_down(game) && !is_wall_on_left(game, 180 + 45)) \
		&& (!is_wall_on_down(game) && !is_wall_on_left(game, 180 + 90))) \
		|| ((!is_wall_on_down(game) && !is_wall_on_right(game,  180 + 45)) \
		&& (!is_wall_on_down(game) && !is_wall_on_right(game, 180 + 90))))
	{
		game->pos_y += game->pdir_y * SPEED;
		game->pos_x -= game->pdir_x * SPEED;
	}
}

void	move_left(t_game *game)
{
	if (!is_wall_on_left(game, 90)) /* should move left when 90 degree its way is free  */
	{
		game->pos_x += cos(degree_to_radian(fix_angle(game->player_angle + 90))) * SPEED; /* new_angle : game->player_angle + 90 */
		game->pos_y -= sin(degree_to_radian(fix_angle(game->player_angle + 90))) * SPEED;
	}
}

void	move_right(t_game *game)
{
	if (!is_wall_on_right(game, 90)) /* without 45 degree, if there was 45 degree, player could not move when intersected with wall on  */
	{
		game->pos_x += cos(degree_to_radian(fix_angle(game->player_angle - 90))) * SPEED;
		game->pos_y -= sin(degree_to_radian(fix_angle(game->player_angle - 90))) * SPEED;
	}
}

/**
 *  max pdir_y : 1, min pdir_y : -1
*/
