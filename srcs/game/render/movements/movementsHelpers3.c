/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movementsHelpers3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:13:15 by adouib            #+#    #+#             */
/*   Updated: 2022/11/06 12:19:27 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

int	is_wall_on_left(t_game *game, int angle)
{
	int		next_move_y;
	int		next_move_x;

	next_move_y = (game->ppos_y - sin(deg_2_rad(\
		fix_angle(game->player_angle + angle))) * SPEED) / SQUARE_HEIGHT;
	next_move_x = (game->ppos_x + cos(deg_2_rad(\
		fix_angle(game->player_angle + angle))) * SPEED) / SQUARE_HEIGHT;
	if (game->map[next_move_y][next_move_x] == '1'
		|| game->map[next_move_y][next_move_x] == ' '
		|| game->map[next_move_y][next_move_x] == '\n'
		|| game->map[next_move_y][next_move_x] == '\0')
		return (1);
	return (0);
}

int	is_wall_on_right(t_game *game, int angle)
{
	int		next_move_y;
	int		next_move_x;

	next_move_y = (game->ppos_y - sin(deg_2_rad(\
		fix_angle(game->player_angle - angle))) * SPEED) / SQUARE_HEIGHT;
	next_move_x = (game->ppos_x + cos(deg_2_rad(\
		fix_angle(game->player_angle - angle))) * SPEED) / SQUARE_HEIGHT;
	if (game->map[next_move_y][next_move_x] == '1'
	|| game->map[next_move_y][next_move_x] == ' '
	|| game->map[next_move_y][next_move_x] == '\n'
	|| game->map[next_move_y][next_move_x] == '\0')
		return (1);
	return (0);
}

int	is_wall_on_down(t_game *game)
{
	int	next_move_y;
	int	next_move_x;

	next_move_y = (game->ppos_y + game->pdir_y * SPEED) / SQUARE_HEIGHT;
	next_move_x = (game->ppos_x - game->pdir_x * SPEED) / SQUARE_WIDTH;
	if (game->map[next_move_y][next_move_x] == '1'
	|| game->map[next_move_y][next_move_x] == ' '
	|| game->map[next_move_y][next_move_x] == '\n'
	|| game->map[next_move_y][next_move_x] == '\0')
		return (1);
	return (0);
}

int	is_wall_on_up(t_game *game)
{
	int	next_move_y;
	int	next_move_x;

	next_move_y = ((game->ppos_y - game->pdir_y * SPEED) / SQUARE_HEIGHT);
	next_move_x = ((game->ppos_x + game->pdir_x * SPEED) / SQUARE_WIDTH);
	if (game->map[next_move_y][next_move_x] == '1'
	|| game->map[next_move_y][next_move_x] == ' '
	|| game->map[next_move_y][next_move_x] == '\n'
	|| game->map[next_move_y][next_move_x] == '\0')
		return (1);
	return (0);
}
