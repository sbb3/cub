/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/10/30 13:57:19 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

/*checking Horizontal intersection – the y-axis*/
void	looking_for_wall_coordinates_horizontally(t_game *game)
{
	int	coordinate_y;
	int	coordinate_x;

	game->wall_hit = 0;
	while (!game->wall_hit)
	{
		coordinate_y = floor(game->yinter / SQUARE_SIZE);
		coordinate_x = floor(game->xinter / SQUARE_SIZE);
		if (out_of_container_width_and_height(game))
			break ;
		if (game->map[coordinate_y] == NULL)
			break ;
		if (game->map[coordinate_y][coordinate_x] == '1')
			break ;
		game->yinter += game->ystep;
		game->xinter += game->xstep;
	}
	// if (game->ray_up)
	// 	game->yinter++;
	game->h_wall_hit_y = game->yinter;
	game->h_wall_hit_x = game->xinter;
}

/*checking vertical intersection – the x-axis*/
void	looking_for_wall_coordinates_vertically(t_game *game)
{
	int	coordinate_y;
	int	coordinate_x;

	game->wall_hit = 0;
	while (!game->wall_hit)
	{
		coordinate_y = floor(game->yinter / SQUARE_SIZE);
		coordinate_x = floor(game->xinter / SQUARE_SIZE);
		if (out_of_container_width_and_height(game))
			break ;
		if (game->map[coordinate_y] == NULL)
			break ;
		if (game->map[coordinate_y][coordinate_x] == '1')
			break ;
		game->xinter += game->xstep;
		game->yinter += game->ystep;
	}
	// if (game->ray_left)
	// 	game->xinter++;
	game->v_wall_hit_y = game->yinter;
	game->v_wall_hit_x = game->xinter;
}

void	intersections_and_steps_horizontally(t_game *game)
{
	game->yinter = (game->pos_y / SQUARE_SIZE) * SQUARE_SIZE;
	if (game->ray_down)
		game->yinter += SQUARE_SIZE;
	if (tan(degree_to_radian(game->ray_angle) == 0))
		game->ray_angle -= degree_to_radian(1);
	game->xinter = (game->pos_x + ((game->pos_y - game->yinter) \
		/ tan(degree_to_radian(game->ray_angle))));
	game->ystep = SQUARE_SIZE;
	if (game->ray_up)
		game->ystep *= -1;
	game->xstep = SQUARE_SIZE / tan(degree_to_radian(game->ray_angle));
	if (game->ray_left && game->xstep > 0)
		game->xstep *= -1;
	if (game->ray_right && game->xstep < 0)
		game->xstep *= -1;
	if (game->ray_up)
		game->yinter--;
}

void	intersections_and_steps_vertically(t_game *game)
{
	game->xinter = (game->pos_x / SQUARE_SIZE) * SQUARE_SIZE;
	if (game->ray_right)
		game->xinter += SQUARE_SIZE;
	game->yinter = (game->pos_y + ((game->pos_x - game->xinter) \
		* tan(degree_to_radian(game->ray_angle))));
	game->xstep = SQUARE_SIZE;
	if (game->ray_left)
		game->xstep *= -1;
	game->ystep = SQUARE_SIZE * tan(degree_to_radian(game->ray_angle));
	if (game->ray_up && game->ystep > 0)
		game->ystep *= -1;
	if (game->ray_down && game->ystep < 0)
		game->ystep *= -1;
	if (game->ray_left)
		game->xinter--;
}
/*
intersections_and_steps_horizontally

	// !!!!1 inf or nan
	if (tan(degree_to_radian(game->ray_angle) == 0))
			game->ray_angle -= degree_to_radian(1);

	// xstep on left down side will be positive so we turn it to negative same as the left up side, is already negative
	if (game->ray_left && game->xstep > 0)
			game->xstep *= -1;

	// xstep on right down side will be negative so we turn it to positive same as the right up side, is already positive
	if (game->ray_right && game->xstep < 0)
		game->xstep *= -1;

	// substract a pixel to check if nextY is in the wall
	if (game->ray_up)
		game->yinter--;


looking_for_wall_coordinates_vertically && looking_for_wall_coordinates_horizontally
	first check if these coordinates are at wall,
 else increment them with ystep and xstep till u find a wall


*/
