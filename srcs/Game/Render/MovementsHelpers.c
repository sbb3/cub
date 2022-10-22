/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MovementsHelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:31:52 by adouib            #+#    #+#             */
/*   Updated: 2022/10/22 16:08:53 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	move_up_down(t_game *game, char c)
{

	if (c == 'u')
	{
		if (game->map[(int)((game->pos_y - game->pdir_y * SPEED) / SQUARE_HEIGHT)]
		[(int)((game->pos_x + game->pdir_x * SPEED) / SQUARE_WIDTH)] == '0')
		{
			game->pos_x += game->pdir_x * SPEED;
			game->pos_y -= game->pdir_y * SPEED; // pdir_y : 1
		}
	}
	else if (c == 'd')
	{
		if (game->map[(int)((game->pos_y + game->pdir_y * SPEED) / SQUARE_HEIGHT)]
		[(int)((game->pos_x - game->pdir_x * SPEED) / SQUARE_WIDTH)] == '0')
		{
			game->pos_x -= game->pdir_x * SPEED;
			game->pos_y += game->pdir_y * SPEED; // up pdir_y : 1, low pdir_y : -1
		}
	}
}

void	move_left_right(t_game *game, char c)
{
	int new_angle; /* new_angle_to_which_player_will_move */
	if (c == 'L') /* move left */
	{
		new_angle = game->player_angle + 90;
		correct_angle(&new_angle);
		if (game->map[(int)((game->pos_y - sin(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)]
		[(int)((game->pos_x + cos(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)] == '0')
		{
			game->pos_x += cos(degreeToRadian(new_angle)) * SPEED;
			game->pos_y -= sin(degreeToRadian(new_angle)) * SPEED;
		}
	}
	else if (c == 'R') /* move right */
	{
		new_angle = game->player_angle - 90;
		correct_angle(&new_angle);
		if (game->map[(int)((game->pos_y - sin(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)]
		[(int)((game->pos_x + cos(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)] == '0')
		{
			game->pos_x += cos(degreeToRadian(new_angle)) * SPEED;
			game->pos_y -= sin(degreeToRadian(new_angle)) * SPEED;
		}
	}
}

void	rotate(t_game *game, char c)
{
	if (c == 'L') /* rotate left */
	{
		game->player_angle += ROTATION;
		correct_player_angle(game);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
	}
	else if (c == 'R') /* rotate right */
	{
		game->player_angle -= ROTATION;
		correct_player_angle(game);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
	}
}

