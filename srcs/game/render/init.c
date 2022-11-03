/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/11/03 10:13:15 by adouib           ###   ########.fr       */
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
	game->win = mlx_new_window(game->mlx, game->window_width, \
		game->window_height, "cubF4KE3D");
	if (!game->win)
		quit(game, "New window initialization failed");
}

/* rays = window_width */
void	init_variables(t_game *game, const char *av[])
{
	game->parser = parser(av);
	game->map = game->parser->map;
	game->map_width = game->parser->width;
	game->map_height = game->parser->height;
	game->window_width = SQUARE_WIDTH * game->map_width;
	game->window_height = SQUARE_HEIGHT * game->map_height;
	game->minimap_width = MINIMAP_SIZE * game->map_width;
	game->minimap_height = MINIMAP_SIZE * game->map_height;
	game->half_win_height = game->window_height / 2;
	game->rays = game->window_width;
	game->pos_x = game->parser->yp * SQUARE_SIZE;
	game->pos_y = game->parser->xp * SQUARE_SIZE;
	game->ray_angle_increment = ((double)FOV / game->rays);
	game->h_hit = 0;
	game->half_fov = FOV / 2;
	game->ceiling_color = rgb_to_hex(game->parser->c->r, game->parser->c->g, \
		game->parser->c->b);
	game->floor_color = rgb_to_hex(game->parser->f->r, game->parser->f->g, \
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
