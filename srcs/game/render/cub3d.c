/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/11/05 22:10:31 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

void old(t_game *game)
 {

 	double rayX = game->pos_x;
 	double rayY = game->pos_y;
 	int floorY;
 	int floorX;
 	int wallHit = 0;
 	while (!wallHit)
 	{
 		rayX += game->pdir_x;
 		rayY += game->pdir_y;
 		floorY = floor(rayY);
 		floorX = floor(rayX);

 		if (game->map[floorY / SQUARE_SIZE][floorX / SQUARE_SIZE] == '1')
 			break;
 	}
 	// game->wallHitX = floorX;
 	// game->wallHitY = floorY;
 }

void	draw(t_game *game)
{
	raycaster(game);
	// minimap(game);
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
