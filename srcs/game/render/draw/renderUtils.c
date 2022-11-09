/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/11/09 21:42:08 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

/*checking Horizontal intersection – the y-axis*/
void	horizontal_wall_coordinates(t_game *game)
{
	int	coordinate_y;
	int	coordinate_x;

	game->wall_hit = 0;
	while (!game->wall_hit)
	{
		coordinate_y = game->yinter / SQUARE_SIZE;
		coordinate_x = game->xinter / SQUARE_SIZE;
		if (out_of_container_width_and_height(game, coordinate_x, coordinate_y))
			break ;
		if (game->map[coordinate_y][coordinate_x] == '1'
		|| game->map[coordinate_y][coordinate_x] == '\0')
			break ;
		game->yinter += game->ystep;
		game->xinter += game->xstep;
	}
	if (game->ray_up)
		game->yinter++;
	game->h_wall_hit_y = game->yinter;
	game->h_wall_hit_x = game->xinter;
}

/*checking vertical intersection – the x-axis*/
void	vertical_wall_coordinates(t_game *game)
{
	int	coordinate_y;
	int	coordinate_x;

	game->wall_hit = 0;
	while (!game->wall_hit)
	{
		coordinate_y = floor(game->yinter / SQUARE_SIZE);
		coordinate_x = floor(game->xinter / SQUARE_SIZE);
		if (out_of_container_width_and_height(game, coordinate_x, coordinate_y))
			break ;
		if (game->map[coordinate_y][coordinate_x] == '1'
		|| game->map[coordinate_y][coordinate_x] == '\0')
			break ;
		game->xinter += game->xstep;
		game->yinter += game->ystep;
	}
	if (game->ray_left)
		game->xinter++;
	game->v_wall_hit_y = game->yinter;
	game->v_wall_hit_x = game->xinter;
}

/*
	yinter and xinter coordinates of the first intersection point either
	on the horizontal or the vertical
*/
void	horizontal_intersection_and_steps(t_game *game)
{
	game->yinter = ((int)game->ppos_y / SQUARE_SIZE) * SQUARE_SIZE;
	if (game->ray_down)
		game->yinter += SQUARE_SIZE;
	if (tan(deg_2_rad(game->ray_angle) == 0))
		game->ray_angle -= deg_2_rad(1);
	game->xinter = (game->ppos_x + ((game->ppos_y - game->yinter) \
		/ tan(deg_2_rad(game->ray_angle))));
	game->ystep = SQUARE_SIZE;
	if (game->ray_up)
		game->ystep *= -1;
	game->xstep = SQUARE_SIZE / tan(deg_2_rad(game->ray_angle));
	if (game->ray_left && game->xstep > 0)
		game->xstep *= -1;
	if (game->ray_right && game->xstep < 0)
		game->xstep *= -1;
	if (game->ray_up)
		game->yinter--;
}

void	vertical_intersection_and_steps(t_game *game)
{
	game->xinter = ((int)game->ppos_x / SQUARE_SIZE) * SQUARE_SIZE;
	if (game->ray_right)
		game->xinter += SQUARE_SIZE;
	game->yinter = (game->ppos_y + ((game->ppos_x - game->xinter) \
		* tan(deg_2_rad(game->ray_angle))));
	game->xstep = SQUARE_SIZE;
	if (game->ray_left)
		game->xstep *= -1;
	game->ystep = SQUARE_SIZE * tan(deg_2_rad(game->ray_angle));
	if (game->ray_up && game->ystep > 0)
		game->ystep *= -1;
	if (game->ray_down && game->ystep < 0)
		game->ystep *= -1;
	if (game->ray_left)
		game->xinter--;
}
