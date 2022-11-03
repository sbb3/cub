/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:59 by adouib            #+#    #+#             */
/*   Updated: 2022/11/03 10:50:45 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	calculations(t_game *game)
{
	get_the_short_distance(game);
	get_projected_wall_height(game);
	if (game->h_hit)
		game->texture_offset_x = (int)game->wall_hit_x % SQUARE_SIZE;
	else
		game->texture_offset_x = (int)game->wall_hit_y % SQUARE_SIZE;
}

void	ray_wall_collision_vertically(t_game *game)
{
	reset_vars_to_zero(game);
	ray_direction(game);
	intersections_and_steps_vertically(game);
	looking_for_wall_coordinates_vertically(game);
}

void	ray_wall_collision_horizontally(t_game *game)
{
	reset_vars_to_zero(game);
	ray_direction(game);
	intersections_and_steps_horizontally(game);
	looking_for_wall_coordinates_horizontally(game);
}

void	raycaster(t_game *game)
{
	int	x;

	game->ray_angle = game->player_angle + game->half_fov;
	correct_angle(&game->ray_angle);
	game->dist_to_wall = (game->window_height / 2) \
		/ tan(deg_2_rad(game->half_fov));
	x = -1;
	while (++x < game->window_width)
	{
		ray_wall_collision_horizontally(game);
		ray_wall_collision_vertically(game);
		calculations(game);
		paint(game, x);
		game->ray_angle -= game->ray_angle_increment;
		correct_angle(&game->ray_angle);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->global_img->frame, \
		0, 0);
}
