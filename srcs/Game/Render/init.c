/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/10/23 18:07:35 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

void init_player_starting_direction(t_game *game)
{
	if (game->parser->p_direction == 'N')
		game->player_angle = 90;
	else if (game->parser->p_direction == 'W')
		game->player_angle = 180;
	else if (game->parser->p_direction == 'S')
		game->player_angle = 270;
	else if (game->parser->p_direction == 'E')
		game->player_angle = 360;
	game->pdir_x = cos(degreeToRadian(game->player_angle)); // player starting rotation angle
	game->pdir_y = sin(degreeToRadian(game->player_angle)); // player starting rotattion angle, should match the sin in the movements function
}

void do_init(t_game *game)
{
	game->map = game->parser->map;
	game->map_width = game->parser->width; // map width length
	game->map_height = game->parser->height;  // map height length

	// printf("x %d\n", game->parser->xp * SQUARE_SIZE);
	// printf("y %d\n", game->parser->yp * SQUARE_SIZE);
	// printf("mw %d\n", game->parser->width);
	// printf("w %d\n", game->parser->width * SQUARE_SIZE);
	game->pos_x =  game->parser->yp * SQUARE_SIZE;			  // init to the starting location on the map;
	game->pos_y = game->parser->xp * SQUARE_SIZE;

	game->ray_angle_increment = ((double)FOV / RAYS); // fov / window_width
	game->horizontal_Hit = 0;
}

t_game *init_variables(const char *av[])
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_if_null(game, "Allocation failed");
	game->parser = parser(av);
	do_init(game);
	init_player_starting_direction(game);
	return game;
}

t_game *init_variables_and_mlx_and_textures(t_game *game, const char *av[])
{
	game = init_variables(av);
	game->mlx = mlx_init();
	if (!game->mlx)
		quit(game, "Connection to the X-Window Server failed");
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cubF4KE3D");
	if (!game->win)
		quit(game, "New window initialization failed");
	game->n_t_data = createNorthTextureImage(game); // create the texture image
	game->s_t_data = createSouthTextureImage(game); // create the texture image
	game->w_t_data = createWestTextureImage(game);	// create the texture image
	game->e_t_data = createEastTextureImage(game);	// create the texture image


	return game;
}
