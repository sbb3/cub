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


t_img_data *createImage(t_game *game)
{
	t_img_data *imgData;

	imgData = ft_calloc(1, sizeof(t_img_data));
	if (!imgData)
		exit_if_null(imgData, "Could not create an image");
	imgData->frame = mlx_new_image(game->mlx, game->windowWidth, game->windowHeight);
	imgData->frame_addr = mlx_get_data_addr(imgData->frame, &imgData->bpp, &imgData->sLine, &imgData->endn);

	return imgData;
}

void deleteImage(t_game *game)
{
	if (game->imgData->frame)
	{
		mlx_destroy_image(game->mlx, game->imgData->frame);
		game->imgData->frame = NULL;
	}
}
