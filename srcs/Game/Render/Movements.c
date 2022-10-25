/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:29:49 by adouib            #+#    #+#             */
/*   Updated: 2022/10/25 16:49:57 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

void	re_draw(t_game *game)
{
	delete_global_image_then_clear_window(game);
	draw(game);
}

int	movements(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		quit(game, NULL);
	if (keycode == W_KEY)
		move_up_down(game, 'u');
	if (keycode == S_KEY)
		move_up_down(game, 'd');
	if (keycode == A_KEY)
		move_left_right(game, 'L');
	if (keycode == D_KEY)
		move_left_right(game, 'R');
	if (keycode == LEFT_KEY)
		rotate(game, 'L');
	if (keycode == RIGHT_KEY)
		rotate(game, 'R');
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
// redraw
// re_draw
