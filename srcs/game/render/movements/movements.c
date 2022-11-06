/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:29:49 by adouib            #+#    #+#             */
/*   Updated: 2022/11/06 13:39:34 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	re_draw(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	raycasting_then_drawing(game);
}

int	movements(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		quit(game, NULL);
	if (keycode == W_KEY)
		move_up(game);
	if (keycode == S_KEY)
		move_down(game);
	if (keycode == A_KEY)
		move_left(game);
	if (keycode == D_KEY)
		move_right(game);
	if (keycode == LEFT_KEY)
		rotate_left(game);
	if (keycode == RIGHT_KEY)
		rotate_right(game);
	re_draw(game);
	return (0);
}
