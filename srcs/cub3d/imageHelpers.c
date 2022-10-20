/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageHelpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:17 by adouib            #+#    #+#             */
/*   Updated: 2022/10/20 13:49:06 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void deleteImages(t_game *game)
{
	if (game->global_img->frame) /* global image freeing */
		mlx_destroy_image(game->mlx, game->global_img->frame);

	if (game->n_t_data->frame) /* texture freeing */
		mlx_destroy_image(game->mlx, game->n_t_data->frame);

	// if (game->s_t_data->frame) /* texture freeing */
	// 	mlx_destroy_image(game->mlx, game->s_t_data->frame);

	// if (game->w_t_data->frame) /* texture freeing */
	// 	mlx_destroy_image(game->mlx, game->w_t_data->frame);

	// if (game->e_t_data->frame) /* texture freeing */
	// 	mlx_destroy_image(game->mlx, game->e_t_data->frame);

}

void coloring_pixel(t_game *game, int x, int y, int color)
{
	// color the pixel on the x, y coordinates
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (y * game->global_img->line_bytes) + (x * (game->global_img->bpp / 8));
	color_pixel = game->global_img->frame_addr + pixelOffset;
	*(unsigned int *)color_pixel = color;
}

unsigned int get_the_color_from_north_texture(t_game *game) // main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
{
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (game->texture_offset_y * game->n_t_data->line_bytes) + (game->texture_offset_x * (game->n_t_data->bpp / 8));
	color_pixel = game->n_t_data->frame_addr + pixelOffset;
	return (*(unsigned int *)color_pixel);
}

unsigned int get_the_color_from_south_texture(t_game *game) // main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
{
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (game->texture_offset_y * game->s_t_data->line_bytes) + (game->texture_offset_x * (game->s_t_data->bpp / 8));
	color_pixel = game->s_t_data->frame_addr + pixelOffset;
	return (*(unsigned int *)color_pixel);
}

unsigned int get_the_color_from_west_texture(t_game *game) // main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
{
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (game->texture_offset_y * game->w_t_data->line_bytes) + (game->texture_offset_x * (game->w_t_data->bpp / 8));
	color_pixel = game->w_t_data->frame_addr + pixelOffset;
	return (*(unsigned int *)color_pixel);
}
unsigned int get_the_color_from_east_texture(t_game *game) // main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
{
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (game->texture_offset_y * game->e_t_data->line_bytes) + (game->texture_offset_x * (game->e_t_data->bpp / 8));
	color_pixel = game->e_t_data->frame_addr + pixelOffset;
	return (*(unsigned int *)color_pixel);
}

void set_the_texture_color_on_walls(t_game *game, int x, int y, unsigned int color)
{
	// color the pixel on the x, y coordinates
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (y * game->global_img->line_bytes) + (x * game->global_img->bpp / 8); // * 4 (4 bytes) // convert from bits to bytes
	color_pixel = game->global_img->frame_addr + pixelOffset;							// points to the first byte in the pixel (4 bytes)
	*(unsigned int *)color_pixel = color;					// main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
																						// write the texture_color on the main image
}


t_global_image *createGlobalImage(t_game *game) /* global image creation*/
{
	t_global_image *image;

	image = ft_calloc(1, sizeof(t_global_image));
	if (!image)
		exit_if_null(image, "Allocation failed");
	image->frame = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!image->frame)
		exit_if_null(image, "Could not create an global image");
	image->frame_addr = mlx_get_data_addr(image->frame, &image->bpp, &image->line_bytes, &image->endn);
	return (image);
}


n_texture *createNorthTextureImage(t_game *game) /* north texture image creation*/
{
	n_texture *data;

	data = ft_calloc(1, sizeof(n_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, NORTH_TEXTURE, &data->w, &data->h);
	if (!data->frame)
		exit_if_null(data, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, &data->line_bytes, &data->endn);
	return (data);
}


s_texture *createSouthTextureImage(t_game *game) /* south texture image creation*/
{
	s_texture *data;

	data = ft_calloc(1, sizeof(s_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, SOUTH_TEXTURE, &data->w, &data->h);
	if (!data->frame)
		exit_if_null(data, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, &data->line_bytes, &data->endn);
	return (data);
}


w_texture *createWestTextureImage(t_game *game) /* w texture image creation*/
{
	w_texture *data;

	data = ft_calloc(1, sizeof(w_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, WEST_TEXTURE, &data->w, &data->h);
	if (!data->frame)
		exit_if_null(data, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, &data->line_bytes, &data->endn);
	return (data);
}

e_texture *createEastTextureImage(t_game *game) /* e texture image creation*/
{
	e_texture *data;

	data = ft_calloc(1, sizeof(e_texture));
	if (!data)
		exit_if_null(data, "Allocation failed");
	data->frame = mlx_xpm_file_to_image(game->mlx, EAST_TEXTURE, &data->w, &data->h);
	if (!data->frame)
		exit_if_null(data, "Could not load the texture from the xpm");
	data->frame_addr = mlx_get_data_addr(data->frame, &data->bpp, &data->line_bytes, &data->endn);
	return (data);
}
