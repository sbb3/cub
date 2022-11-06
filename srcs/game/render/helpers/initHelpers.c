/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initHelpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 01:54:02 by adouib            #+#    #+#             */
/*   Updated: 2022/11/06 02:05:01 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

int	map_height(char *s[])
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	map_width(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	calc_each_row_columns_then_get_the_max_col(t_game *game)
{
	int	rows;
	int	y;
	int	max;

	rows = map_height(game->parser->map);
	game->cols = ft_calloc(rows + 1, sizeof(int));
	if (!game->cols)
		exit_if_null(game->cols, "Allocation failed");
	y = -1;
	while (++y < rows)
		game->cols[y] = map_width(game->parser->map[y]);
	game->cols[y] = 0;
	y = -1;
	while (++y < rows)
	{
		if (max < game->cols[y])
			max = game->cols[y];
	}
	return (max);
}
