/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:34:21 by adouib            #+#    #+#             */
/*   Updated: 2022/10/27 22:29:48 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

/* WALL STRETCHING FIX using these 2 arguments,
and dont reset wall_bottom_pixel and wall_top_pixel */
void	paint_walls_helper_function(t_game *game, int *y, int *end)
{
	if (game->wall_height > game->window_height)
	{
		*y = 0;
		*end = game->window_height;
	}
	else
	{
		*y = game->wall_top_pixel;
		*end = game->wall_bottom_pixel;
	}
}

void	paint_walls(t_game *game, int startX)
{
	float			scaling_factor;
	unsigned int	color;
	int				y;
	int				end;

	ray_direction(game);
	scaling_factor = (double)TEXTURE_HEIGHT / game->wall_height;
	paint_walls_helper_function(game, &y, &end);
	while (y < end)
	{
		game->texture_offset_y = (y - game->wall_top_pixel) * scaling_factor;
		if (game->is_north && game->h_hit)
			color = get_the_color_from_north_texture(game);
		else if (game->is_west && !game->h_hit)
			color = get_the_color_from_west_texture(game);
		else if (game->is_south && game->h_hit)
			color = get_the_color_from_south_texture(game);
		else if (game->is_east && !game->h_hit)
			color = get_the_color_from_east_texture(game);
		set_the_texture_color_on_walls(game, startX, y, color);
		y++;
	}
}

/* draw_floor : starting from wall_bottom_pixel
going by x and drawing each y pixel */
void	paint_floor(t_game *game, int x)
{
	int	start_x;
	int	start_y;
	int	end_y;

	start_x = x;
	start_y = game->wall_bottom_pixel;
	end_y = game->window_height;
	while (start_y < end_y)
	{
		coloring_pixel(game, start_x, start_y, game->parser->c->cl);
		start_y++;
	}
}

/* draw_ceiling : starting from start_y = 0
going by x and drawing each y pixel along the y axis */
void	paint_ceiling(t_game *game, int x)
{
	int	start_x;
	int	start_y;
	int	end_y;

	start_x = x;
	start_y = 0;
	end_y = game->wall_top_pixel;
	while (start_y < end_y)
	{
		coloring_pixel(game, start_x, start_y, game->parser->f->cl);
		start_y++;
	}
}

void	paint(t_game *game, int x)
{
	paint_ceiling(game, x);
	paint_floor(game, x);
	paint_walls(game, x);
}

/*

paint_walls_helper_function:
if (game->wall_height > game->window_height)
	{
		y = 0;
		end = game->window_height;
	}
	else
	{						// if there is only these 2 statements below, and the protection for resetting walltoppixel and wallbottompixel to 0 and game->window_height, it will start taking the color pixel from the texture at index 0, not dependng on the wallProjectedHeight
		y = game->wall_top_pixel; // y should always start with;
		end = game->wall_bottom_pixel;
	}


paint_walls:  // sizeX or width of the strip(column) will be 1, but since it is 1, there is no need to specify it here
while (y < end) // start drawing from the wall_top_pixel till wall_bottom_pixel , this distance is equal to projectedWallHeight
	{
		// calculate the offsetY
		// when projected_wall_height > game->window_height, wall_top_pixel will be negative and the sign -, then it will be positive
		game->texture_offset_y = (y - wall_top_pixel) * scaling_factor; // what pixel color to pick from the texture
		// is_north
		if (game->is_north && game->h_hit)
			color = get_the_color_from_north_texture(game); // hex color not rgb // the texture pixel color that will drawn on the globalImage
		// is_west
		else if (game->is_west && !game->h_hit)
			color = get_the_color_from_west_texture(game); // hex color not rgb // the texture pixel color that will drawn on the globalImage
		// is_south
		else if (game->is_south && game->h_hit)
			color = get_the_color_from_south_texture(game);
		// is_east texture
		else if (game->is_east && !game->h_hit)
			color = get_the_color_from_east_texture(game);

		set_the_texture_color_on_walls(game, startX, y, color);
		y++;
	}

*/
