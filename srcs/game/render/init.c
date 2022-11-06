/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:56 by adouib            #+#    #+#             */
/*   Updated: 2022/11/06 01:25:52 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

// pdir_x : player starting rotation angle
/* pdfir_y : player starting rotattion angle,
	should match the sin in the movements function */
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
	game->pdir_x = cos(deg_2_rad(game->player_angle));
	game->pdir_y = sin(deg_2_rad(game->player_angle));
}

// create the textures images
void	init_textures(t_game *game)
{
	game->global_img = create_global_image(game);
	game->n_t_data = create_north_texture_image(game);
	game->s_t_data = create_south_texture_image(game);
	game->w_t_data = create_west_texture_image(game);
	game->e_t_data = create_east_texture_image(game);
}

void	init_minilibx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		quit(game, "Connection to the X-Window Server failed");
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, \
		WINDOW_HEIGHT, "cubF4KE3D");
	if (!game->win)
		quit(game, "New window initialization failed");
}

/* rays = window_width */
void	init_variables(t_game *game, const char *av[])
{
	game->parser = parser(av);
	game->map = game->parser->map;
	game->map_height = map_height(game->map);
	game->map_width = calc_each_row_columns(game);
	printf("w dyali : %d\n", game->map_width);
	game->rays = WINDOW_WIDTH;
	game->pos_x = game->parser->yp * SQUARE_SIZE + 32;
	game->pos_y = game->parser->xp * SQUARE_SIZE + 32;
	game->ray_angle_increment = ((double)FOV / game->rays);
	game->h_hit = 0;
	game->half_fov = FOV / 2;
	game->ceiling_color = rgb_to_hex(game->parser->c->r, game->parser->c->g, \
		game->parser->c->b);
	game->floor_color = rgb_to_hex(game->parser->f->r, game->parser->f->g, \
		game->parser->f->b);
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

int	get_max(t_game *game, int rows)
{
	game->cols = ft_calloc(rows + 1, sizeof(int));
	int y = -1;
	while (++y < rows)
	{
		game->cols[y] = map_width(game->parser->map[y]);
		printf("%d\n", game->cols[y]);
	}
	game->cols[y] = 0;
	int tmp = game->cols[0];
	for (int i = 1; i < rows; ++i) {
		if (tmp < game->cols[i]) {
			tmp = game->cols[i];
		}
	}
 	return tmp;
 }

int	calc_each_row_columns(t_game *game)
{
	int	rows;
	int	y;

	rows = map_height(game->parser->map);
	printf("h : %d\n", game->parser->height);
	printf("w : %d\n", game->parser->width);
	printf("r dyali : %d\n", rows);
	game->cols = ft_calloc(rows + 1, sizeof(int));
	if (!game->cols)
		exit_if_null(game->cols, "Allocation failed");
	y = -1;
	while (++y < rows)
		game->cols[y] = map_width(game->parser->map[y]);
	game->cols[y] = 0;
	int tmp = game->cols[0];
	for (int i = 1; i < rows; ++i) {
		if (tmp < game->cols[i]) {
			tmp = game->cols[i];
		}
	}
	return tmp;
}
