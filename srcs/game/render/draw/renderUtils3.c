/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderUtils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/11/06 11:57:42 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	reset_vars_to_zero(t_game *game)
{
	game->yinter = 0;
	game->xinter = 0;
	game->ystep = 0;
	game->xstep = 0;
	game->ray_up = 0;
	game->ray_down = 0;
	game->ray_left = 0;
	game->ray_right = 0;
	game->is_north = 0;
	game->is_south = 0;
	game->is_west = 0;
	game->is_east = 0;
}

void	ray_direction(t_game *game)
{
	if (game->ray_angle > 0 && game->ray_angle <= 180)
	{
		game->ray_up = 1;
		game->is_north = 1;
	}
	else if (!game->is_north && !game->ray_up)
	{
		game->ray_down = 1;
		game->is_south = 1;
	}
	if (game->ray_angle >= 90 && game->ray_angle < 270)
	{
		game->ray_left = 1;
		game->is_west = 1;
	}
	else if (!game->is_west && !game->ray_left)
	{
		game->ray_right = 1;
		game->is_east = 1;
	}
}

float	distance(float startX, float startY, float endX, float endY)
{
	return (sqrt(pow((fabs(endX - startX)), 2) + \
		pow((fabs(endY - startY)), 2)));
}

/* doesnt stop or tied to/at window height and width,
but attached to the map element size * width or height */
int	out_of_container_width_and_height(t_game *game, int coordinate_x, \
	int coordinate_y)
{
	if (game->yinter < 0 || game->yinter >= (SQUARE_HEIGHT * game->map_height))
		return (1);
	if (game->xinter < 0 || game->xinter >= (SQUARE_WIDTH * game->map_width))
		return (1);
	if (coordinate_y > game->map_height \
		|| coordinate_x > game->cols[coordinate_y])
		return (1);
	return (0);
}
