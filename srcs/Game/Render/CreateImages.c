/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateImages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:50:46 by adouib            #+#    #+#             */
/*   Updated: 2022/10/25 16:02:20 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

/* global image creation*/
t_global_image	*create_global_image(t_game *game)
{
	t_global_image	*image;

	image = ft_calloc(1, sizeof(t_global_image));
	if (!image)
		exit_if_null(image, "Allocation failed");
	image->frame = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!image->frame)
		exit_if_null(image->frame, "Could not create an global image");
	image->frame_addr = mlx_get_data_addr(image->frame, &image->bpp, \
		&image->line_bytes, &image->endn);
	return (image);
}

/* north texture image creation*/
n_texture	*create_north_texture_image(t_game *game)
{
	n_texture	*data;

	data = ft_calloc(1, sizeof(n_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, NORTH_TEXTURE, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}

/* south texture image creation*/
s_texture	*create_south_texture_image(t_game *game)
{
	s_texture	*data;

	data = ft_calloc(1, sizeof(s_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, SOUTH_TEXTURE, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}

/* w texture image creation*/
w_texture	*create_west_texture_image(t_game *game)
{
	w_texture	*data;

	data = ft_calloc(1, sizeof(w_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, WEST_TEXTURE, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}

/* e texture image creation*/
e_texture	*create_east_texture_image(t_game *game)
{
	e_texture	*data;

	data = ft_calloc(1, sizeof(e_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, EAST_TEXTURE, \
		&data->w, &data->h);
	if (!data->frame)
		exit_if_null(data->frame, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, \
		&data->line_bytes, &data->endn);
	if (!data->frame_addr)
		exit_if_null(data->frame_addr, "Could not get the frame data");
	return (data);
}
