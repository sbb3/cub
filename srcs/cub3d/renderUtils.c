/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:33 by adouib            #+#    #+#             */
/*   Updated: 2022/10/15 19:21:52 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int distance(int startX, int startY, int endX, int endY)
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
	if (game->ray_angle >= 0 && game->ray_angle <= 180)
		game->ray_up = 1;
	else if (game->ray_angle > 180 && game->ray_angle <= 360)
		game->ray_down = 1;
	if (game->ray_angle >= 90 && game->ray_angle <= 270)
		game->ray_left = 1;
	else if ((game->ray_angle >= 0 && game->ray_angle < 90) || (game->ray_angle > 270 && game->ray_angle <= 360))
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

void looking_for_wall_coordinates_vertically(t_game *game)
{
	game->wall_hit = 0;
	while (!game->wall_hit) // checking vertical intersection – the x-axis
	{
		if (out_of_container_width_and_height(game))
			break;
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)][(int)floor(game->xinter / SQUARE_SIZE)] == '1')
			break;
		game->xinter += game->xstep;
		game->yinter += game->ystep;
	}
	game->vertical_wall_hit_y = game->yinter;
	game->vertical_wall_hit_x = game->xinter;
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
	game->wall_top_pixel = HALF_WINDOW_HEIGHT - (game->projected_wall_height / 2); // wallHeight drawing start postion on the y-axis
	if (game->wall_top_pixel < 0)
		game->wall_top_pixel = 0;
	game->wall_bottom_pixel = HALF_WINDOW_HEIGHT + (game->projected_wall_height / 2);
	if (game->wall_bottom_pixel > WINDOW_HEIGHT)
		game->wall_bottom_pixel = WINDOW_HEIGHT;
}

void get_projected_wall_height(t_game *game)
{
	// !!!!! fix fishe eye
	game->correct_distance = game->distance_to_wall * (cos(degreeToRadian(game->ray_angle - game->player_angle)));
	// !!!!! distance To Projectddd Wall
	game->projected_wall_height = (double)(SQUARE_HEIGHT * game->distance_to_projected_wall) / game->correct_distance;
	if (game->projected_wall_height > WINDOW_HEIGHT)
		game->projected_wall_height = WINDOW_HEIGHT;
}

void get_the_short_distance(t_game *game)
{
	if (game->horizontal_distance_to_wall < game->vertical_distance_to_wall)
	{
		game->horizontal_Hit = 1;
		game->wall_hit_x = game->horizontal_wall_hit_x;
		game->wall_hit_y = game->horizontal_wall_hit_y;
		game->distance_to_wall = game->horizontal_distance_to_wall;
	}
	else
	{
		game->horizontal_Hit = 0;
		game->wall_hit_x = game->vertical_wall_hit_x;
		game->wall_hit_y = game->vertical_wall_hit_y;
		game->distance_to_wall = game->vertical_distance_to_wall;
	}
}
