/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageHelpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:17 by adouib            #+#    #+#             */
/*   Updated: 2022/10/15 19:19:40 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void deleteImages(t_game *game)
{
	if (game->global_img->frame) /* global image freeing */
		mlx_destroy_image(game->mlx, game->global_img->frame);

	if (game->texture_data->frame) /* texture freeing */
		mlx_destroy_image(game->mlx, game->texture_data->frame);
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

unsigned int get_the_color_from_texture(t_game *game) // main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
{
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (game->texture_offset_y * game->texture_data->line_bytes) + (game->texture_offset_x * (game->texture_data->bpp / 8));
	color_pixel = game->texture_data->frame_addr + pixelOffset;
	return (*(unsigned int *)color_pixel);
}

void set_the_texture_color_on_walls(t_game *game, int x, int y, int color)
{
	// color the pixel on the x, y coordinates
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (y * game->global_img->line_bytes) + (x * game->global_img->bpp / 8); // * 4 (4 bytes) // convert from bits to bytes
	color_pixel = game->global_img->frame_addr + pixelOffset;							// points to the first byte in the pixel (4 bytes)
	*(unsigned int *)color_pixel = game->texture_data->texture_color;					// main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
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

t_texture *createTextureImage(t_game *game) /* texture image creation*/
{
	t_texture *texture_data;

	texture_data = ft_calloc(1, sizeof(t_texture));
	if (!texture_data)
		exit_if_null(texture_data, "Allocation failed");
	texture_data->frame = mlx_xpm_file_to_image(game->mlx, TEXTURE, &texture_data->w, &texture_data->h);
	if (!texture_data->frame)
		exit_if_null(texture_data, "Could not load the texture from the xpm");
	texture_data->frame_addr = mlx_get_data_addr(texture_data->frame, &texture_data->bpp, &texture_data->line_bytes, &texture_data->endn);
	return (texture_data);
}
