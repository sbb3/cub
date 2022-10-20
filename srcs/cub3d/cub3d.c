/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/10/20 12:19:19 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void draw(t_game *game)
{
	// dont create the images on each render
	game->global_img = createGlobalImage(game);		// create the global image
	game->n_t_data = createNorthTextureImage(game); // create the texture image
	game->s_t_data = createSouthTextureImage(game); // create the texture image
	game->w_t_data = createWestTextureImage(game); // create the texture image
	game->e_t_data = createEastTextureImage(game); // create the texture image
	raycasting(game);
	minimap(game);
}

int main(int ac, const char *av[])
{
	t_game *game;

	if (ac != 2)
		quit(NULL, "Format: ./cub3d <map name>.cub");
	game = init_variables(av);
	// parser(av, game);
	mlx_and_images_init(game);
	draw(game); // !! will get removed and used the render function
	// mlx_loop_hook(game->mlx, render, game); // infinite loop -> drawing
	mlx_hook(game->win, 2, 0L, movements, game);
	mlx_hook(game->win, 17, 0L, red_cross_quit, game);
	mlx_loop(game->mlx);
}

/*
debug
*/
