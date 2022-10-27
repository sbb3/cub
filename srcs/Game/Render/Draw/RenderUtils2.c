/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderUtils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/10/27 22:30:03 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

void	get_the_short_distance(t_game *game)
{
	game->v_dist_to_wall = distance(game->pos_x, game->pos_y, \
		game->v_wall_hit_x, game->v_wall_hit_y);
	game->h_dist_to_wall = distance(game->pos_x, game->pos_y, \
		game->h_wall_hit_x, game->h_wall_hit_y);
	if (game->h_dist_to_wall < game->v_dist_to_wall)
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
		* cos(degree_to_radian(game->ray_angle - game->player_angle));
}

/* calculing the projected wall hegiht, then from it,
we calc the top and bottom pixel of the wall */
void	get_projected_wall_height(t_game *game)
{
	game->wall_height = (double)(SQUARE_HEIGHT * game->dist_to_wall) \
		/ game->ray_distance;
	game->wall_top_pixel = game->half_win_height \
		- (double)(game->wall_height / 2);
	game->wall_bottom_pixel = game->half_win_height \
		+ (double)(game->wall_height / 2);
}

/*
get_wall_top_bottom_pixels
// / when HALF_game->window_height < game->window_height, wall_top_pixel will be negative
	game->wall_top_pixel = HALF_game->window_height - (double)(game->projected_wall_height / 2); // wallHeight drawing start postion on the y-axis
	// if (game->wall_top_pixel < 0)
	// 	game->wall_top_pixel = 0;
	game->wall_bottom_pixel = HALF_game->window_height + (double)(game->projected_wall_height / 2);
	// (double) in case projected_wall_height low than 2, will not return a 0, but a double value like 0.22545
	// if (game->wall_bottom_pixel > game->window_height)
		// game->wall_bottom_pixel = game->window_height;

	// printf("t : %d\n", game->wall_top_pixel);
	// printf("b : %d\n", game->wall_bottom_pixel);


get_projected_wall_height
	if (game->projected_wall_height > game->window_height)
	{
		game->test2 = game->projected_wall_height;
		// game->projected_wall_height = game->window_height;
	}
	// printf("%lf\n", game->projected_wall_height);


get_the_short_distance
	game->distorted_ray_distance_to_wall = game->h_dist_to_wall;
		// !!!!! fix fishe eye : he red rays all have a different lenght, so would compute different wall heights for different vertical stripes, hence the rounded effect. The green rays on the right all have the same length, so will give the correct result. The same still apllies for when the player rotates (then the camera plane is no longer horizontal and the green lines will have different lengths, but still with a constant change between each) and the walls become diagonal but straight lines on the screen. This explanation is somewhat handwavy but gives the idea.
		// lodev fisheye explains it


		// printf("cd = %lf : rd = %lf : cos(ra - pa) = %lf\n", game->ray_distance, game->distorted_ray_distance_to_wall, cos(degree_to_radian(game->ray_angle - game->player_angle)));

*/
