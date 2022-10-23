/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/10/23 18:33:40 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

float distance(int startX, int startY, int endX, int endY)
{
	return (sqrt(pow((abs(endX - startX)), 2) + pow((abs(endY - startY)), 2)));
}

void reset_vars_to_zero(t_game *game)
{
	// deltaY  // deltaX | // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall
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

int out_of_container_width_and_height(t_game *game)
{
	if (game->yinter < 0 || game->yinter >= WINDOW_HEIGHT)
		return 1;
	if (game->xinter < 0 || game->xinter > WINDOW_WIDTH)
		return 1;
	return 0;
}

void check_ray_direction(t_game *game)
{
	if (game->ray_angle > 0 && game->ray_angle <= 180)
		game->ray_up = 1;
	else if (game->ray_angle > 180 && game->ray_angle <= 360)
		game->ray_down = 1;
	if (game->ray_angle >= 90 && game->ray_angle < 270)
		game->ray_left = 1;
	else if ((game->ray_angle >= 270 && game->ray_angle <= 360) || (game->ray_angle >= 0 && game->ray_angle < 90))
		game->ray_right = 1;
}

void correct_player_angle(t_game *game)
{
	if (game->player_angle < 0)
		game->player_angle = 360 + game->player_angle;
	if (game->player_angle > 360)
		game->player_angle = game->player_angle - 360;
	// 360%360=0; 0%360=0; 362%360=2 42%360=42; -1%360=359
	// return (angle % 360); // a<0 360-a < 360-360=0 <a-360
}

void correct_ray_angle(t_game *game)
{
	if (game->ray_angle < 0)
		game->ray_angle = 360 + game->ray_angle;
	if (game->ray_angle > 360)
		game->ray_angle = game->ray_angle - 360;
}

void looking_for_wall_coordinates_horizontally(t_game *game)
{

	game->wall_hit = 0;
	while (!game->wall_hit) // checking Horizontal intersection – the y-axis
	{
		if (out_of_container_width_and_height(game))
			break;
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)][(int)floor(game->xinter / SQUARE_SIZE)] == '1')
			break;
		game->yinter += game->ystep;
		game->xinter += game->xstep;
	}

	game->horizontal_wall_hit_y = game->yinter;
	game->horizontal_wall_hit_x = game->xinter;
}

void looking_for_wall_coordinates_vertically(t_game *game)
{
	game->wall_hit = 0;
	while (!game->wall_hit) // checking vertical intersection – the x-axis
	{
		if (out_of_container_width_and_height(game))
			break;
		// printf("%lf\n", game->yinter);

			// printf("xi : %d\n", (int)floor(game->xinter / SQUARE_SIZE));
			// printf("yi : %lf\n", (int)floor(game->yinter/ SQUARE_SIZE));
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)] == NULL) {
			break;
		}
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)][(int)floor(game->xinter / SQUARE_SIZE)] == '1') {
			break;
		}
		game->xinter += game->xstep;
		game->yinter += game->ystep;
	}
	if (game->ray_left)
		game->xinter++;
	game->vertical_wall_hit_y = game->yinter;
	game->vertical_wall_hit_x = game->xinter;
}

void intersections_and_steps_horizontally(t_game *game)
{
	game->yinter = (game->pos_y / SQUARE_SIZE) * SQUARE_SIZE; // floor it
	if (game->ray_down)
		game->yinter += SQUARE_SIZE;
	if (tan(degreeToRadian(game->ray_angle) == 0)) // !!!!1 inf or nan
		game->ray_angle -= degreeToRadian(1);
	game->xinter = (game->pos_x + ((game->pos_y - game->yinter) / tan(degreeToRadian(game->ray_angle)))); // absolute (yinter - pos_y)
	game->ystep = SQUARE_SIZE;
	if (game->ray_up)
		game->ystep *= -1;
	game->xstep = SQUARE_SIZE / tan(degreeToRadian(game->ray_angle));
	if (game->ray_left && game->xstep > 0)
		game->xstep *= -1; // xstep on left down side will be positive so we turn it to negative same as the left up side, is already negative
	if (game->ray_right && game->xstep < 0)
		game->xstep *= -1; // xstep on right down side will be negative so we turn it to positive same as the right up side, is already positive
	if (game->ray_up)
		game->yinter--; // substract a pixel to check if nextY is in the wall
}

void intersections_and_steps_vertically(t_game *game)
{
	// calc xinter
	game->xinter = (game->pos_x / SQUARE_SIZE) * SQUARE_SIZE; // floor it
	if (game->ray_right)
		game->xinter += SQUARE_SIZE;
	// calc yinter
	game->yinter = (game->pos_y + ((game->pos_x - game->xinter) * tan(degreeToRadian(game->ray_angle))));
	// calc xstep
	game->xstep = SQUARE_SIZE;
	if (game->ray_left)
		game->xstep *= -1;
	// calc ystep
	game->ystep = SQUARE_SIZE * tan(degreeToRadian(game->ray_angle));
	if (game->ray_up && game->ystep > 0)
		game->ystep *= -1;
	if (game->ray_down && game->ystep < 0)
		game->ystep *= -1;
	if (game->ray_left)
		game->xinter--;
}

void get_wall_top_bottom_pixels(t_game *game)
{
	// / when HALF_WINDOW_HEIGHT < WINDOW_HEIGHT, wall_top_pixel will be negative
	game->wall_top_pixel = HALF_WINDOW_HEIGHT - (double)(game->projected_wall_height / 2); // wallHeight drawing start postion on the y-axis
	// if (HALF_WINDOW_HEIGHT < pwh)
	// {
	// 	game->wall_top_pixel = (double)(game->projected_wall_height / 2) - HALF_WINDOW_HEIGHT;
	// }
	// if (game->wall_top_pixel < 0)
	// 	game->wall_top_pixel = 0;
	game->wall_bottom_pixel = HALF_WINDOW_HEIGHT + (double)(game->projected_wall_height / 2); // (double) in case projected_wall_height low than 2, will not return a 0, but a double value like 0.22545
	// if (game->wall_bottom_pixel > WINDOW_HEIGHT)
		// game->wall_bottom_pixel = WINDOW_HEIGHT;

	// printf("t : %d\n", game->wall_top_pixel);
	// printf("b : %d\n", game->wall_bottom_pixel);
}
// int k = 0;
void get_projected_wall_height(t_game *game)
{
	// !!!!! distance To Projectddd Wall
	game->projected_wall_height = (double)(SQUARE_HEIGHT * game->distance_to_projected_wall) / game->correct_ray_distance;
	if (game->projected_wall_height > WINDOW_HEIGHT) {
		game->test2 = game->projected_wall_height;
		// game->projected_wall_height = WINDOW_HEIGHT;
	}

	// printf("%lf\n", game->projected_wall_height);
}

void get_the_short_distance(t_game *game)
{
	game->vertical_distance_to_wall = distance(game->pos_x, game->pos_y, game->vertical_wall_hit_x, game->vertical_wall_hit_y);
	game->horizontal_distance_to_wall = distance(game->pos_x, game->pos_y, game->horizontal_wall_hit_x, game->horizontal_wall_hit_y);

	if (game->horizontal_distance_to_wall < game->vertical_distance_to_wall)
	{
		game->horizontal_Hit = 1;
		game->wall_hit_x = game->horizontal_wall_hit_x;
		game->wall_hit_y = game->horizontal_wall_hit_y;
		game->distorted_ray_distance_to_wall = game->horizontal_distance_to_wall;
		// !!!!! fix fishe eye : he red rays all have a different lenght, so would compute different wall heights for different vertical stripes, hence the rounded effect. The green rays on the right all have the same length, so will give the correct result. The same still apllies for when the player rotates (then the camera plane is no longer horizontal and the green lines will have different lengths, but still with a constant change between each) and the walls become diagonal but straight lines on the screen. This explanation is somewhat handwavy but gives the idea.
		// lodev fisheye explains it
	}
	else
	{
		game->horizontal_Hit = 0;
		game->wall_hit_x = game->vertical_wall_hit_x;
		game->wall_hit_y = game->vertical_wall_hit_y;
		game->distorted_ray_distance_to_wall = game->vertical_distance_to_wall;
		// !!!!! fix fishe eye : he red rays all have a different lenght, so would compute different wall heights for different vertical stripes, hence the rounded effect. The green rays on the right all have the same length, so will give the correct result. The same still apllies for when the player rotates (then the camera plane is no longer horizontal and the green lines will have different lengths, but still with a constant change between each) and the walls become diagonal but straight lines on the screen. This explanation is somewhat handwavy but gives the idea.
	}
	game->correct_ray_distance = game->distorted_ray_distance_to_wall * cos(degreeToRadian(game->ray_angle - game->player_angle));

	// printf("cd = %lf : rd = %lf : cos(ra - pa) = %lf\n", game->correct_ray_distance, game->distorted_ray_distance_to_wall, cos(degreeToRadian(game->ray_angle - game->player_angle)));
}
// floor(cos(degreeToRadian(game->ray_angle - game->player_angle)) * 100) / 100));
