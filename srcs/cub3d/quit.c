/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:08:14 by adouib            #+#    #+#             */
/*   Updated: 2022/09/26 23:33:25 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

char **free_map(char **token)
{
	int i;

	i = 0;
	while (token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
	return (NULL);
}

void deleteImage(t_game *game)
{
	if (game->imgData->frame)
	{
		mlx_destroy_image(game->mlx, game->imgData->frame);
		game->imgData->frame = NULL;
	}
}

void quit(t_game *game, char *s)
{
	if (s)
	{
		printf("%s\n", "Error");
		printf("%s\n", s);
		if (!game)
			exit(1);
	}
	if (game->map)
		free_map(game->map);
	if (game->imgData->frame)
		mlx_destroy_image(game->mlx, game->imgData->frame);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	exit(0);
}

/* when user press the red cross button, the window should be closed*/
int red_cross_quit(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->imgData->frame)
		mlx_destroy_image(game->mlx, game->imgData->frame);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	exit(0);
	return (0);
}
