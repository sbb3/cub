/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/10/29 15:42:18 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

/*create the global image, its height and width are the window scales,
the main image which will draw on it the minimap and the raycasting stuff*/
void	draw(t_game *game)
{
	// game->global_img = create_global_image(game);
	raycaster(game);
	minimap(game);
}

int	main(int ac, const char *av[])
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		quit(NULL, "Format: ./cub3d <map name>.cub");
	game = init_variables_and_mlx_and_textures(game, av);
	draw(game);
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
