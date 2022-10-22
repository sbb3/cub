/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/10/22 17:46:50 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void init_player_starting_direction(t_game *game)
{
	// change with the map character
	char c = 'N';

	if (c == 'N')
		game->player_angle = 90;
	else if (c == 'W')
		game->player_angle = 180;
	else if (c == 'S')
		game->player_angle = 270;
	else if (c == 'E')
		game->player_angle = 360;
	game->pdir_x = cos(degreeToRadian(game->player_angle)); // player starting rotation angle
	game->pdir_y = sin(degreeToRadian(game->player_angle)); // player starting rotattion angle, should match the sin in the movements function
}

void do_init(t_game *game)
{
	game->map_width = mapWidth(game->map[0]); // map width length
	game->map_height = mapHeight(game->map);  // map height length
	game->pos_x = WINDOW_WIDTH / 2;			  // init to the starting location on the map
	game->pos_y = WINDOW_HEIGHT / 2;
	game->ray_angle_increment = ((double)FOV / RAYS); // fov / window_width
	game->minimap_width = MINIMAP_SIZE * game->map_width;
	game->minimap_height = MINIMAP_SIZE * game->map_height;
	game->horizontal_Hit = 0;
}

t_game *init_variables(const char *av[])
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_if_null(game, "Allocation failed");
	game->map = map_read(av, game);
	if (!game->map)
		quit(NULL, "map is empty");
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
