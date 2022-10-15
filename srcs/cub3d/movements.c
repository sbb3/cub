/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:29:49 by adouib            #+#    #+#             */
/*   Updated: 2022/10/15 21:01:29 by adouib           ###   ########.fr       */
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
	correct_player_angle(game); // no need for this
	if (keycode == ESC_KEY)
		quit(game, NULL);
	if (keycode == W_KEY)
	{
		if (game->map[(int)((game->pos_y + game->pdir_y * SPEED) / SQUARE_HEIGHT)]
					 [(int)((game->pos_x + game->pdir_x * SPEED) / SQUARE_WIDTH)] == '0')
		{
			game->pos_x += game->pdir_x * SPEED;
			game->pos_y -= game->pdir_y * SPEED; // pdir_y : 1
		}
		// printf("x : %d\n", game->pos_x);
		// printf("y : %d\n", game->pos_y);
		// printf("dirx : %lf\n", floor(game->pdir_x * SPEED));
		// printf("diry : %lf\n", floor(game->pdir_y * SPEED));
	}
	if (keycode == S_KEY)
	{
		if (game->map[(int)((game->pos_y - game->pdir_y * SPEED) / SQUARE_HEIGHT)]
					 [(int)((game->pos_x - game->pdir_x * SPEED) / SQUARE_WIDTH)] == '0')
		{
			game->pos_x -= game->pdir_x * SPEED;
			game->pos_y += game->pdir_y * SPEED; // up pdir_y : 1, low pdir_y : -1
		}
		system("clear");
		// printf("x : %d\n", game->pos_x);
		// printf("y : %d\n", game->pos_y);
		// printf("dirx : %lf\n", game->pdir_x * SPEED);
		// printf("diry : %lf\n", game->pdir_y * SPEED);
	}
	if (keycode == A_KEY)
	{
		int new_pos_x = game->pos_x;
		int new_pos_y = game->pos_y;

		int new_angle_in_degrees = game->player_angle + 90;
		if (new_angle_in_degrees < 0)
			new_angle_in_degrees = 360 + new_angle_in_degrees;
		if (new_angle_in_degrees > 360)
			new_angle_in_degrees = new_angle_in_degrees - 360;

		// int left = 0;
		// int right = 0;
		// int up = 0;
		// int down = 0;

		// // here change it to new angle
		// if (game->player_angle >= 90 && game->player_angle < 270)
		// 	left = 1;
		// else if ((game->player_angle > 0 && game->player_angle < 90) || (game->player_angle > 270 && game->player_angle < 360))
		// 	right = 1;

		// if (game->player_angle >= 0 && game->player_angle <= 180)
		// 	up = 1;
		// else if (game->player_angle > 180 && game->player_angle <= 360)
		// 	down = 1;

		// if (up && left) {
		new_pos_x += cos(degreeToRadian(new_angle_in_degrees)) * SPEED;
		new_pos_y -= sin(degreeToRadian(new_angle_in_degrees)) * SPEED;
		// }
		// if (up && right) {
		// 	new_pos_x += cos(degreeToRadian(new_angle_in_degrees)) * SPEED ;
		// 	new_pos_y -= sin(degreeToRadian(new_angle_in_degrees)) * SPEED;
		// }

		// if (down && left) {
		// 	new_pos_x += cos(degreeToRadian(new_angle_in_degrees)) * SPEED ;
		// 	new_pos_y -= sin(degreeToRadian(new_angle_in_degrees)) * SPEED;
		// }
		// if (down && right) {
		// 	new_pos_x += cos(degreeToRadian(new_angle_in_degrees)) * SPEED ;
		// 	new_pos_y -= sin(degreeToRadian(new_angle_in_degrees)) * SPEED;
		// }

		// system("clear");

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

		game->pos_x = new_pos_x;
		game->pos_y = new_pos_y;
	}
	if (keycode == D_KEY)
	{
		int new_angle_in_degrees = game->player_angle - 90;
		if (new_angle_in_degrees < 0)
			new_angle_in_degrees = 360 + new_angle_in_degrees;
		if (new_angle_in_degrees > 360)
			new_angle_in_degrees = new_angle_in_degrees - 360;

		// I should x--; cos new_angle is already -
		// I should x++; cos new_angle is already +
		// I should y--; cos new_angle is already +
		// I should y++; cos new_angle is already -
		// refer to the drawing for more explanation
		game->pos_x += cos(degreeToRadian(new_angle_in_degrees)) * SPEED;
		game->pos_y -= sin(degreeToRadian(new_angle_in_degrees)) * SPEED;
	}
	if (keycode == LEFT_KEY)
	{
		game->player_angle += ROTATION;
		correct_player_angle(game);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
		// printf("pdir_x %lf\n", game->pdir_x);
		// printf("pdir_y %lf\n", game->pdir_y);
		// printf("pa %d\n", game->player_angle);
	}
	if (keycode == RIGHT_KEY)
	{
		game->player_angle -= ROTATION;
		correct_player_angle(game);
		game->pdir_x = cos(degreeToRadian(game->player_angle));
		game->pdir_y = sin(degreeToRadian(game->player_angle));
		correct_player_angle(game);
		// printf("pdir_x %lf\n", game->pdir_x);
		printf("pdir_y %lf\n", game->pdir_y);
		// printf("pa %d\n", game->player_angle);
	}
	re_draw(game);
	return (0);
}

/*








*/
