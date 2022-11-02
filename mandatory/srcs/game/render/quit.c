/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:08:14 by adouib            #+#    #+#             */
/*   Updated: 2022/10/30 11:38:37 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

char	**free_map(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
	return (NULL);
}

void	quit(t_game *game, char *s)
{
	if (s)
	{
		printf("%s\n", "Error");
		printf("%s\n", s);
		if (!game)
			exit(1);
	}
	free_all(game);
	exit(EXIT_FAILURE);
}

int	red_cross_quit(t_game *game)
{
	free_all(game);
	exit(EXIT_SUCCESS);
	return (0);
}

void	exit_if_null(void *p, char *message)
{
	if (!p)
	{
		perror(message);
		exit(EXIT_FAILURE);
	}
}
