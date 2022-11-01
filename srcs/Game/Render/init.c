/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/11/01 21:17:47 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

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
	game->pdir_x = cos(deg_2_rad(game->player_angle)); /*player starting rotation angle*/
	game->pdir_y = sin(deg_2_rad(game->player_angle)); /*player starting rotattion angle, should match the sin in the movements function*/
}

void	init_textures(t_game *game)
{
	game->global_img = create_global_image(game);
	game->n_t_data = create_north_texture_image(game); /*create the texture image*/
	game->s_t_data = create_south_texture_image(game); /*create the texture image*/
	game->w_t_data = create_west_texture_image(game);  /*create the texture image*/
	game->e_t_data = create_east_texture_image(game);  /*create the texture image*/
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
	game->ray_angle_increment = ((double)FOV / game->rays); /* fov / game->rays = game->window_width */
	game->h_hit = 0;
	game->half_fov = FOV / 2;
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
