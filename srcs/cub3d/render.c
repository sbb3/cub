#include "../../incl/cub3d.h"

int intersection(t_game *game, double x1, double y1, double x2, double y2) // https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
{
	// wall start coordinates (13, 4)
	// wall end coordinates (13, 8)

	double x3 = (game->map_width / 2);
	double y3 = (game->map_height / 2);
	double x4 = x3 + (game->dirX);
	double y4 = y3 + (game->dirY);

	double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0)
		return 1;

	// vectors t and u
	double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

	if (t > 0 && t < 1 && u > 0)
		return 1;
	return 0;
}

int	distance(int startY, int startX, int endY, int endX)
{
	return sqrt(pow((abs(endX - startX)), 2) + pow((abs(endY - startY)), 2));
}


void edit_pixel(char *frame_addr, int size_line, int bits_per_pixel, int x, int y, int color)
{
	char *color_pixel = frame_addr + ((y * size_line) + (x * (bits_per_pixel / 8)));
	*(int *)color_pixel = color;
}

void drawWall(t_game *game)
{
	int bits_per_pixel;
	int size_line;
	int endian;
	char *frame_addr;

	game->frame_img = mlx_new_image(game->mlx, IMG_WIDTH, IMG_HEIGHT);

	int y = 0;
	int x;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
			{
				frame_addr = mlx_get_data_addr(game->frame_img, &bits_per_pixel, &size_line, &endian);

				for (int yy = 0; yy < IMG_HEIGHT; yy++)
				{
					for (int xx = 0; xx < IMG_WIDTH; xx++)
						edit_pixel(frame_addr, size_line, bits_per_pixel, xx, yy, 0x01804d);
				}
			}
			else
			{
				frame_addr = mlx_get_data_addr(game->frame_img, &bits_per_pixel, &size_line, &endian);

				for (int yy = 0; yy < IMG_HEIGHT; yy++)
				{
					for (int xx = 0; xx < IMG_WIDTH; xx++)
						edit_pixel(frame_addr, size_line, bits_per_pixel, xx, yy, 0x752e02);
				}
			}
			mlx_put_image_to_window(game->mlx, game->win, game->frame_img, x * IMG_WIDTH, y * IMG_HEIGHT);
			x++;
		}
		y++;
	}
}

void drawLine(t_game *game, int startY, int startX, int endY, int endX, int color)
{
	// pythaghors equation
	int pixelsCount = distance(startY, startX, endY, endX); // number of pixels will be in the line or the distance ! https://www.mathsisfun.com/algebra/distance-2-points.html
	double pixelX = startX;
	double pixelY = startY;

	while (pixelsCount)
	{
		mlx_pixel_put(game->mlx, game->win, pixelX, pixelY, color);
		pixelX += game->dirX; // dirX = direction, default to 0, range  [ -1 < 0 < 1 ]
		pixelY += game->dirY; // dirY = direction, default to -1, range [ -1 < 0 < 1 ]
		pixelsCount--;
	}

}

void	drawRect(t_game *game, int startY, int startX, int sizeY, int sizeX, int color)
{

	game->img_data->frame = mlx_new_image(game->mlx, sizeX, sizeY);
	game->img_data->frame_addr = mlx_get_data_addr(game->img_data->frame, &game->img_data->bits_per_pixel, &game->img_data->size_line, &game->img_data->endian);

	int y = 0;
	int x;
	while (y < sizeY)
	{
		x = 0;
		while (x < sizeX)
		{
			edit_pixel(game->img_data->frame_addr, game->img_data->size_line, game->img_data->bits_per_pixel, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_data->frame, startX, startY);
}

void	rayCasting(t_game *game)
{

	double rayX = game->posX;
	double rayY = game->posY;

	int wallHit = 0;
	while (!wallHit)
	{
		rayX += game->dirX;
		rayY += game->dirY;
		int floorY = floor(rayY);
		int floorX = floor(rayX);

		if (game->map[floorY / IMG_HEIGHT][floorX / IMG_WIDTH] == '1')
			break;
	}

	drawLine(game, game->posY, game->posX , rayY, rayX, 0xcfc08);
}

int render(t_game *game)
{
	drawWall(game);
	drawRect(game, game->posY, game->posX, 10, 10, 0xcfc08);
	rayCasting(game);

	return 0;
}
