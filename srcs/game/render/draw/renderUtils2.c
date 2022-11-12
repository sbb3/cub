/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderUtils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/11/12 11:07:56 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	get_the_short_distance(t_game *game)
{
	game->v_dist_to_wall = distance(game->ppos_x, game->ppos_y, \
		game->v_wall_hit_x, game->v_wall_hit_y);
	game->h_dist_to_wall = distance(game->ppos_x, game->ppos_y, \
		game->h_wall_hit_x, game->h_wall_hit_y);
	if (game->h_dist_to_wall <= game->v_dist_to_wall)
	{
		game->h_hit = 1;
		game->wall_hit_x = game->h_wall_hit_x;
		game->wall_hit_y = game->h_wall_hit_y;
		game->distorted_ray_distance_to_wall = game->h_dist_to_wall;
	}
	else
	{
		game->h_hit = 0;
		game->wall_hit_x = game->v_wall_hit_x;
		game->wall_hit_y = game->v_wall_hit_y;
		game->distorted_ray_distance_to_wall = game->v_dist_to_wall;
	}
	game->ray_distance = game->distorted_ray_distance_to_wall \
		* cos(deg_2_rad(game->ray_angle - game->player_angle));
}

/* calculing the projected wall height, then from it,
we calc the top and bottom pixel of the wall */
void	get_projected_wall_height(t_game *game)
{
	game->wall_height = (double)(SQUARE_HEIGHT * \
		game->dist_to_projection_plane) / game->ray_distance;
	game->wall_top_pixel = (WINDOW_HEIGHT / 2) \
		- (double)(game->wall_height / 2);
	game->wall_bottom_pixel = (WINDOW_HEIGHT / 2) \
		+ (double)(game->wall_height / 2);
}
