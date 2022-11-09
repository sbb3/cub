/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/11/09 12:53:25 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

// pdir_x : player starting rotation angle
/* pdfir_y : player starting rotattion angle,
	should match the sin in the movements function */
void	init_player_starting_direction(t_game *game)
{
	if (game->parser->p_direction == 'N')
		game->player_angle = 90;
	else if (game->parser->p_direction == 'W')
		game->player_angle = 180;
	else if (game->parser->p_direction == 'S')
		game->player_angle = 270;
	else if (game->parser->p_direction == 'E')
		game->player_angle = 360;
	game->pdir_x = cos(deg_2_rad(game->player_angle));
	game->pdir_y = sin(deg_2_rad(game->player_angle));
}

// create the textures images
void	init_textures(t_game *game)
{
	game->global_img = create_global_image(game);
	game->n_t_data = create_north_texture_image(game);
	game->s_t_data = create_south_texture_image(game);
	game->w_t_data = create_west_texture_image(game);
	game->e_t_data = create_east_texture_image(game);
}

void	init_minilibx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		quit(game, "Connection to the X-Window Server failed");
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, \
		WINDOW_HEIGHT, "cubF4KE3D");
	if (!game->win)
		quit(game, "New window initialization failed");
}

/* rays = window_width
+ 0.5 to make the player in the center of the square,
ex: coords(2, 4) => (2.5, 4.5)*/
/*
	rgb_encoding : store the rgb decimals colors into a single decimal color,
	if printed using %i will print the decimal version,
	if printed uing %x will print print the hex version
*/
void	init_variables(t_game *game, const char *av[])
{
	game->parser = parser(av);
	game->map = game->parser->map;
	game->map_height = map_height(game->map);
	game->map_width = calc_each_row_columns_then_get_the_max_col(game);
	game->rays = WINDOW_WIDTH;
	game->ppos_x = (game->parser->yp + 0.5) * SQUARE_SIZE;
	game->ppos_y = (game->parser->xp + 0.5) * SQUARE_SIZE;
	game->ray_angle_increment = ((double)FOV / game->rays);
	game->h_hit = 0;
	game->half_fov = FOV / 2;
	game->ceiling_color = rgb_encoding(game->parser->c->r, game->parser->c->g, \
		game->parser->c->b);
	game->floor_color = rgb_encoding(game->parser->f->r, game->parser->f->g, \
		game->parser->f->b);
	init_player_starting_direction(game);
}

t_game	*init_variables_and_mlx_and_textures(t_game *game, const char *av[])
{
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_if_null(game, "Allocation failed");
	init_variables(game, av);
	init_minilibx(game);
	init_textures(game);
	return (game);
}
