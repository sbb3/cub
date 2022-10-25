/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MovementsHelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:31:52 by adouib            #+#    #+#             */
/*   Updated: 2022/10/25 17:10:28 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

void	move_up_down(t_game *game, char c)
{
	if (c == 'u')
	{
		if (game->map[(int)((game->pos_y - game->pdir_y * SPEED) / SQUARE_HEIGHT)]
					 [(int)((game->pos_x + game->pdir_x * SPEED) / SQUARE_WIDTH)] != '1')
		{
			game->pos_x += game->pdir_x * SPEED;
			/* pdir_y : 1 */
			game->pos_y -= game->pdir_y * SPEED;
		}
	}
	else if (c == 'd')
	{
		if (game->map[(int)((game->pos_y + game->pdir_y * SPEED) / SQUARE_HEIGHT)]
					 [(int)((game->pos_x - game->pdir_x * SPEED) / SQUARE_WIDTH)] != '1')
		{
			game->pos_x -= game->pdir_x * SPEED;
			/* up pdir_y : 1, low pdir_y : -1 */
			game->pos_y += game->pdir_y * SPEED;
		}
	}
}

void	move_left_right(t_game *game, char c)
{
	/* new_angle_to_which_player_will_move */
	float	new_angle;
	 /* move left */
	if (c == 'L')
	{
		new_angle = game->player_angle + 90;
		correct_angle(&new_angle);
		if (game->map[(int)((game->pos_y - sin(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)]
					 [(int)((game->pos_x + cos(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)] != '1')
		{
			game->pos_x += cos(degreeToRadian(new_angle)) * SPEED;
			game->pos_y -= sin(degreeToRadian(new_angle)) * SPEED;
		}
	}
	/* move right */
	else if (c == 'R')
	{
		new_angle = game->player_angle - 90;
		correct_angle(&new_angle);
		if (game->map[(int)((game->pos_y - sin(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)]
					 [(int)((game->pos_x + cos(degreeToRadian(new_angle)) * SPEED) / SQUARE_HEIGHT)] != '1')
		{
			game->pos_x += cos(degreeToRadian(new_angle)) * SPEED;
			game->pos_y -= sin(degreeToRadian(new_angle)) * SPEED;
		}
	}
}

void	rotate(t_game *game, char c)
{
	/* rotate left */
	if (c == 'L')
	{
		game->player_angle += ROTATION;
		correct_angle(&game->player_angle);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
	}
	 /* rotate right */
	else if (c == 'R')
	{
		game->player_angle -= ROTATION;
		correct_angle(&game->player_angle);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
	}
}
