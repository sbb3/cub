/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:29:49 by adouib            #+#    #+#             */
/*   Updated: 2022/10/19 13:38:45 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void re_draw(t_game *game)
{
	deleteImages(game);
	mlx_clear_window(game->mlx, game->win);
	draw(game);
}

int movements(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		quit(game, NULL);
	if (keycode == W_KEY)
	{

		if (game->map[(int)((game->pos_y - game->pdir_y * SPEED) / SQUARE_HEIGHT)]
					 [(int)((game->pos_x + game->pdir_x * SPEED) / SQUARE_WIDTH)] == '0')
		{

			game->pos_x += game->pdir_x * SPEED;
			game->pos_y -= game->pdir_y * SPEED; // pdir_y : 1
		}
	}
	if (keycode == S_KEY)
	{
		if (game->map[(int)((game->pos_y + game->pdir_y * SPEED) / SQUARE_HEIGHT)]
					[(int)((game->pos_x - game->pdir_x * SPEED) / SQUARE_WIDTH)] == '0')
		{
			game->pos_x -= game->pdir_x * SPEED;
			game->pos_y += game->pdir_y * SPEED; // up pdir_y : 1, low pdir_y : -1
		}
	}
	if (keycode == A_KEY)
	{
		int new_angle_to_which_player_will_move;

		new_angle_to_which_player_will_move = game->player_angle + 90;
		if (new_angle_to_which_player_will_move < 0)
			new_angle_to_which_player_will_move = 360 + new_angle_to_which_player_will_move;
		if (new_angle_to_which_player_will_move > 360)
			new_angle_to_which_player_will_move = new_angle_to_which_player_will_move - 360;

		int wally = ((game->pos_y + sin(degreeToRadian(new_angle_to_which_player_will_move)) * SPEED) / SQUARE_HEIGHT);
		int wallx = ((game->pos_x += cos(degreeToRadian(new_angle_to_which_player_will_move)) * SPEED) / SQUARE_HEIGHT);
		if (game->map[wally][wallx] == '0')
			{
				game->pos_x += cos(degreeToRadian(new_angle_to_which_player_will_move)) * SPEED;
				game->pos_y -= sin(degreeToRadian(new_angle_to_which_player_will_move)) * SPEED;
			}
	}
	if (keycode == D_KEY)
	{
		int new_angle_to_which_player_will_move;

		new_angle_to_which_player_will_move = game->player_angle - 90;
		if (new_angle_to_which_player_will_move < 0)
			new_angle_to_which_player_will_move = 360 + new_angle_to_which_player_will_move;
		if (new_angle_to_which_player_will_move > 360)
			new_angle_to_which_player_will_move = new_angle_to_which_player_will_move - 360;

		game->pos_x += cos(degreeToRadian(new_angle_to_which_player_will_move)) * SPEED;
		game->pos_y -= sin(degreeToRadian(new_angle_to_which_player_will_move)) * SPEED;
	}
	if (keycode == LEFT_KEY)
	{
		game->player_angle += ROTATION;
		correct_player_angle(game);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
	}
	if (keycode == RIGHT_KEY)
	{
		game->player_angle -= ROTATION;
		correct_player_angle(game);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
	}
	re_draw(game);
	return (0);
}

/*



{
	A AND D KEYS

	// printf("left %d\n", left);
		// printf("right %d\n", right);
		// printf("up %d\n", up);
		// printf("down %d\n", down);
		// printf("pa %d\n", game->player_angle);
		// printf("na %d\n", new_angle_in_degrees);
		// printf("cos(na) %lf\n", cos(degreeToRadian(new_angle_in_degrees)));
		// printf("sin(na) %lf\n", sin(degreeToRadian(new_angle_in_degrees)));
		// printf("new_pos_x %d\n", new_pos_x);
		// printf("new_pos_y %d\n", new_pos_y);
		// printf("pos_x %d\n", game->pos_x);
		// printf("pos_y %d\n", game->pos_y);


		// I should x--; cos new_angle is already -
		// I should x++; cos new_angle is already +
		// I should y--; cos new_angle is already +
		// I should y++; cos new_angle is already -
		// refer to the drawing for more explanation

}

*/
