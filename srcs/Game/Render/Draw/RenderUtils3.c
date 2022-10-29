/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderUtils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/10/29 11:39:36 by adouib           ###   ########.fr       */
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
	else if (game->ray_angle > 180 && game->ray_angle <= 360)
	{
		game->ray_down = 1;
		game->is_south = 1;
	}
	if (game->ray_angle >= 90 && game->ray_angle < 270)
	{
		game->ray_left = 1;
		game->is_west = 1;
	}
	else if ((game->ray_angle >= 270 && game->ray_angle <= 360) \
		|| (game->ray_angle >= 0 && game->ray_angle < 90))
	{
		game->ray_right = 1;
		game->is_east = 1;
	}
}

float	distance(int startX, int startY, int endX, int endY)
{
	return (sqrt(pow((abs(endX - startX)), 2) + pow((abs(endY - startY)), 2)));
}

int	out_of_container_width_and_height(t_game *game)
{
	if (game->yinter < 0 || game->yinter >= game->window_height)
		return (1);
	if (game->xinter < 0 || game->xinter > game->window_width)
		return (1);
	return (0);
}
