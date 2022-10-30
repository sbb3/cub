/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MovementsHelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:31:52 by adouib            #+#    #+#             */
/*   Updated: 2022/10/30 17:09:08 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	move_up(t_game *game)
{
	int	next_move_y;
	int	next_move_x;

	next_move_y = ((game->pos_y - game->pdir_y * SPEED) / SQUARE_HEIGHT);
	next_move_x = ((game->pos_x + game->pdir_x * SPEED) / SQUARE_WIDTH);
	if (game->map[next_move_y][next_move_x] != '1')
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
	if (game->map[next_move_y][next_move_x] != '1')
	{
		game->pos_y += game->pdir_y * SPEED;
		game->pos_x -= game->pdir_x * SPEED;
	}
}

void	move_left(t_game *game)
{
	float	new_angle;
	int		next_move_y;
	int		next_move_x;

	new_angle = game->player_angle + 90;
	correct_angle(&new_angle);
	next_move_y = (game->pos_y - sin(degree_to_radian(new_angle)) * SPEED) \
		/ SQUARE_HEIGHT;
	next_move_x = (game->pos_x + cos(degree_to_radian(new_angle)) * SPEED) \
		/ SQUARE_HEIGHT;
	if (game->map[next_move_y][next_move_x] != '1')
	{
		game->pos_x += cos(degree_to_radian(new_angle)) * SPEED;
		game->pos_y -= sin(degree_to_radian(new_angle)) * SPEED;
	}
}

void	move_right(t_game *game)
{
	float	new_angle;
	int		next_move_y;
	int		next_move_x;

	new_angle = game->player_angle - 90;
	correct_angle(&new_angle);
	next_move_y = (game->pos_y - sin(degree_to_radian(new_angle)) * SPEED) \
		/ SQUARE_HEIGHT;
	next_move_x = (game->pos_x + cos(degree_to_radian(new_angle)) * SPEED) \
		/ SQUARE_HEIGHT;
	if (game->map[next_move_y][next_move_x] != '1')
	{
		game->pos_x += cos(degree_to_radian(new_angle)) * SPEED;
		game->pos_y -= sin(degree_to_radian(new_angle)) * SPEED;
	}
}

/**
 *  max pdir_y : 1, min pdir_y : -1
*/
