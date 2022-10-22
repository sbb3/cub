/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/10/22 19:22:31 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void draw(t_game *game)
{
	game->global_img = createGlobalImage(game); // create the global image
	raycasting(game);
	minimap(game);
}

int main(int ac, const char *av[])
{
	t_game *game;

	if (ac != 2)
		quit(NULL, "Format: ./cub3d <map name>.cub");
	// game->map = parser(av);
	game = init_variables_and_mlx_and_textures(game, av); /* print the address of game in subfunctions */
	draw(game); // !! will get removed and used the render function
	mlx_hook(game->win, 2, 0L, movements, game);
	mlx_hook(game->win, 17, 0L, red_cross_quit, game);
	mlx_loop(game->mlx);
}

/*
debug
*/


// int	render(t_game *game)
// {
// 	draw(game);
// 	usleep(33 * 1000);
// 	return 0;
// }
