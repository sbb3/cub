/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createImages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:50:46 by adouib            #+#    #+#             */
/*   Updated: 2022/11/05 19:34:07 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incl/cub3d.h"

/* global image creation*/
t_global_image	*create_global_image(t_game *game)
{
	t_global_image	*image;

	image = ft_calloc(1, sizeof(t_global_image));
	if (!image)
		exit_if_null(image, "Allocation failed");
	image->frame = mlx_new_image(game->mlx, WINDOW_WIDTH, \
		WINDOW_HEIGHT);
	if (!image->frame)
		exit_if_null(image->frame, "Could not create an global image");
	image->frame_addr = mlx_get_data_addr(image->frame, &image->bpp, \
		&image->line_bytes, &image->endn);
	return (image);
}

/* north texture image creation*/
t_n_texture	*create_north_texture_image(t_game *game)
{
	t_n_texture	*data;
	char		*texture_path;

	texture_path = game->parser->no->path;
	data = ft_calloc(1, sizeof(t_n_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, texture_path, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the north texture");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}

/* south texture image creation*/
t_s_texture	*create_south_texture_image(t_game *game)
{
	t_s_texture	*data;
	char		*texture_path;

	texture_path = game->parser->so->path;
	data = ft_calloc(1, sizeof(t_s_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, texture_path, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the south texture");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}

/* west texture image creation*/
t_w_texture	*create_west_texture_image(t_game *game)
{
	t_w_texture	*data;
	char		*texture_path;

	texture_path = game->parser->we->path;
	data = ft_calloc(1, sizeof(t_w_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, texture_path, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the west texture");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}

/* east texture image creation*/
t_e_texture	*create_east_texture_image(t_game *game)
{
	t_e_texture	*data;
	char		*texture_path;

	texture_path = game->parser->ea->path;
	data = ft_calloc(1, sizeof(t_e_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, texture_path, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the east texture");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}
