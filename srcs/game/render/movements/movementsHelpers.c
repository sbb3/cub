/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movementsHelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:31:52 by adouib            #+#    #+#             */
/*   Updated: 2022/11/03 17:52:17 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	move_up(t_game *game)
{
	system("clear");
	printf("%d\n", is_wall_on_up(game));
	printf("%d\n", is_wall_on_left(game, 45));
	printf("%d\n", is_wall_on_right(game, 45));
	if ((!is_wall_on_up(game) && !is_wall_on_left(game, 45))
		|| (!is_wall_on_up(game) && !is_wall_on_right(game, 45)))
	{
		game->pos_y -= game->pdir_y * SPEED;
		game->pos_x += game->pdir_x * SPEED;
	}
}

void	move_down(t_game *game)
{
	if (((!is_wall_on_down(game) && !is_wall_on_left(game, 180 + 45)) \
		|| (!is_wall_on_down(game) && !is_wall_on_right(game, 180 + 45))))
	{
		game->pos_y += game->pdir_y * SPEED;
		game->pos_x -= game->pdir_x * SPEED;
	}
}

/* new_angle : game->player_angle + 90 */
/* !is_wall_on_left(90) : should move left on 90 degree
when its path is free  */
void	move_left(t_game *game)
{
	if ((!is_wall_on_left(game, 90) && !is_wall_on_up(game)) \
		|| (!is_wall_on_left(game, 90) && !is_wall_on_down(game)))
	{
		game->pos_x += cos(deg_2_rad(fix_angle(game->player_angle + 90))) \
			* SPEED;
		game->pos_y -= sin(deg_2_rad(fix_angle(game->player_angle + 90))) \
			* SPEED;
	}
}

/* (!is_wall_on_right(90))if there was 45 degree,
player could not move when intersected with wall on  */
void	move_right(t_game *game)
{
	if ((!is_wall_on_right(game, 90) && !is_wall_on_up(game)) \
		|| (!is_wall_on_right(game, 90) && !is_wall_on_down(game)))
	{
		game->pos_x += cos(deg_2_rad(fix_angle(game->player_angle - 90))) \
			* SPEED;
		game->pos_y -= sin(deg_2_rad(fix_angle(game->player_angle - 90))) \
			* SPEED;
	}
}
