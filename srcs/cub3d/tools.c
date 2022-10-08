#include "../../incl/cub3d.h"

static void ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = 0;
}

void *ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

int mapWidth(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int mapHeight(char *s[])
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int search_map(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_global_img_data *createGlobalImage(t_game *game)
{
	t_global_img_data *imgData;

	imgData = ft_calloc(1, sizeof(t_global_img_data));
	if (!imgData)
		exit_if_null(imgData, "Could not create an image");
	imgData->frame = mlx_new_image(game->mlx, game->windowWidth, game->windowHeight);
	imgData->frame_addr = mlx_get_data_addr(imgData->frame, &imgData->bpp, &imgData->line_bytes, &imgData->endn);

	return imgData;
}

t_texture *createTextureImage(t_game *game)
{
	t_texture *texture_data;

	texture_data = ft_calloc(1, sizeof(t_texture));
	if (!texture_data)
		exit_if_null(texture_data, "Could not create an image");
	texture_data->frame = mlx_new_image(game->mlx, game->windowWidth, game->windowHeight);
	texture_data->frame_addr = mlx_get_data_addr(texture_data->frame, &texture_data->bpp, &texture_data->line_bytes, &texture_data->endn);

	return texture_data;
}

void deleteImage(t_game *game)
{
	// if (game->imgData->frame)
	// {
	// 	mlx_destroy_image(game->mlx, game->imgData->frame);
	// 	game->imgData->frame = NULL;
	// }
	// if (game->imgData->frame_addr)
	// {
	// 	free(game->imgData->frame_addr);
	// }
	if (game->globalImgData)
	{
		free(game->globalImgData);
	}
}
