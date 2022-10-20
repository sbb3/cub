/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:59 by adouib            #+#    #+#             */
/*   Updated: 2022/10/20 13:57:47 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

// first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall

void ray_direction(t_game *game)
{
	if (game->ray_angle > 0 && game->ray_angle <= 180)
		game->is_north = 1;
	else if (game->ray_angle > 180 && game->ray_angle <= 360)
		game->is_south = 1;
	if (game->ray_angle >= 90 && game->ray_angle < 270)
		game->is_west = 1;
	else if ((game->ray_angle >= 270 && game->ray_angle <= 360) || (game->ray_angle >= 0 && game->ray_angle < 90))
		game->is_east = 1;
}

void draw_texture_colors_on_walls(t_game *game, int startX, int wall_top_pixel, int wall_bottom_pixel) // sizeX or width of the strip(column) will be 1, but since it is 1, there is no need to specify it here
{
	float scaling_factor;
	unsigned int color;
	int y;

	ray_direction(game);
	if (game->projected_wall_height != WINDOW_HEIGHT)
		scaling_factor = (double)TEXTURE_HEIGHT / game->projected_wall_height; // projectedWallHeight
	else
		scaling_factor = (double)TEXTURE_HEIGHT / game->test2;


	y = wall_top_pixel;
	while (y < wall_bottom_pixel) // start drawing from the wall_top_pixel till wall_bottom_pixel , this distance is equal to projectedWallHeight
	{
		// calculate the offsetY
		game->texture_offset_y = (y - wall_top_pixel) * scaling_factor; // what pixel color to pick from the texture
		// is_north
		if (game->is_north && game->horizontal_Hit)
			color = get_the_color_from_north_texture(game); // hex color not rgb // the texture pixel color that will drawn on the globalImage
		// is_west
		else if (game->is_west && !game->horizontal_Hit)
			color = get_the_color_from_west_texture(game); // hex color not rgb // the texture pixel color that will drawn on the globalImage
		// is_south
		else if (game->is_south && game->horizontal_Hit)
			color = get_the_color_from_south_texture(game);
		// is_east texture
		else if (game->is_east && !game->horizontal_Hit)
			color = get_the_color_from_east_texture(game);

		set_the_texture_color_on_walls(game, startX, y, color);
		y++;
	}
}

void draw_ceiling_floor(t_game *game, int startX, int startY, int endY, int color)
{
	// draw_ceiling : starting from 0
	// draw_floor : starting from wall_bottom_pixel
	// going by x and drawing each y pixel
	while (startY < endY)
	{
		coloring_pixel(game, startX, startY, color);
		// mlx_pixel_put(game->mlx, game->win, startX, startY, color);
		startY++;
	}
	// printf("%d\n", endY);
}

void calculations(t_game *game)
{
	get_the_short_distance(game);
	get_projected_wall_height(game);
	get_wall_top_bottom_pixels(game);
	if (game->horizontal_Hit)
		game->texture_offset_x = (int)game->wall_hit_x % SQUARE_SIZE;
	else
		game->texture_offset_x = (int)game->wall_hit_y % SQUARE_SIZE;
}

void ray_wall_collision_vertically(t_game *game)
{
	reset_vars_to_zero(game);
	check_ray_direction(game);
	intersections_and_steps_vertically(game);
	looking_for_wall_coordinates_vertically(game);
}

void ray_wall_collision_horizontally(t_game *game)
{
	reset_vars_to_zero(game);
	check_ray_direction(game);
	intersections_and_steps_horizontally(game);
	looking_for_wall_coordinates_horizontally(game);
}

void raycasting(t_game *game) // 64 grid
{
	int x;
	system("clear");

	game->ray_angle = game->player_angle + HALF_FOV;
	correct_ray_angle(game);
	game->distance_to_projected_wall = (WINDOW_HEIGHT / 2) / tan(degreeToRadian(HALF_FOV));
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		ray_wall_collision_horizontally(game);
		ray_wall_collision_vertically(game);
		calculations(game);
		draw_ceiling_floor(game, x, 0, game->wall_top_pixel, 0x454745);				   // draw the ceil
		draw_ceiling_floor(game, x, game->wall_bottom_pixel, WINDOW_HEIGHT, 0x808a83); // draw the floor
		draw_texture_colors_on_walls(game, x, game->wall_top_pixel, game->wall_bottom_pixel);
		// printf("%lf\n", game->ray_angle);
		game->ray_angle -= game->ray_angle_increment; // needed for drawing next ray // if it goes over 360, will reset to 0 + rayAngle
		correct_ray_angle(game);
		// printf("%d\n", game->projected_wall_height);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->global_img->frame, 0, 0);
}
