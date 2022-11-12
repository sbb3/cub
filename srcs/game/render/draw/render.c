/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:59 by adouib            #+#    #+#             */
/*   Updated: 2022/11/12 10:53:41 by adouib           ###   ########.fr       */
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

void	vertical_wall_collision(t_game *game)
{
	reset_vars_to_zero(game);
	ray_direction(game);
	vertical_intersection_and_steps(game);
	vertical_wall_coordinates(game);
}

void	horizontal_wall_collision(t_game *game)
{
	reset_vars_to_zero(game);
	ray_direction(game);
	horizontal_intersection_and_steps(game);
	horizontal_wall_coordinates(game);
}

void	raycasting_then_drawing(t_game *game)
{
	int	x;

	game->ray_angle = game->player_angle + game->half_fov;
	correct_angle(&game->ray_angle);
	game->dist_to_projection_plane = (WINDOW_HEIGHT / 2) \
		/ tan(deg_2_rad(game->half_fov));
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		horizontal_wall_collision(game);
		vertical_wall_collision(game);
		calculations(game);
		paint(game, x);
		game->ray_angle -= game->ray_angle_increment;
		correct_angle(&game->ray_angle);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->global_img->frame, \
		0, 0);
}
