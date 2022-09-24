#include "../../incl/cub3d.h"

int k = 1;

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

int distance(int startY, int startX, int endY, int endX)
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

	game->frame_img = mlx_new_image(game->mlx, SQUARE_WIDTH, SQUARE_HEIGHT);

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

				for (int yy = 0; yy < SQUARE_HEIGHT; yy++)
				{
					for (int xx = 0; xx < SQUARE_WIDTH; xx++)
						edit_pixel(frame_addr, size_line, bits_per_pixel, xx, yy, 0x01804d);
				}
			}
			else
			{
				frame_addr = mlx_get_data_addr(game->frame_img, &bits_per_pixel, &size_line, &endian);

				for (int yy = 0; yy < SQUARE_HEIGHT; yy++)
				{
					for (int xx = 0; xx < SQUARE_WIDTH; xx++)
						edit_pixel(frame_addr, size_line, bits_per_pixel, xx, yy, 0x752e02);
				}
			}
			mlx_put_image_to_window(game->mlx, game->win, game->frame_img, x * SQUARE_WIDTH, y * SQUARE_HEIGHT);
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
		pixelX += game->rayAngleX; // dirX = direction, default to 0, range  [ -1 < 0 < 1 ]
		pixelY += game->rayAngleY; // dirY = direction, default to -1, range [ -1 < 0 < 1 ]
		pixelsCount--;
	}
}
void drawLinePlayer(t_game *game, int startY, int startX, int endY, int endX, int color)
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
void drawRect(t_game *game, int startY, int startX, int sizeY, int sizeX, int color)
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
	drawLinePlayer(game, game->posY, game->posX, y * 100, x * 100, 0xffffff);

	// if (game->rotationAngle > 359)
	// 	game->rotationAngle -= 360;
	// if (game->rotationAngle < 0)
	// 	game->rotationAngle = 0;
	// printf("%d\n", game->rotationAngle);
	// if (game->rotationAngle > 0 && game->rotationAngle < 180) {
	// 	game->rayUp = 1;
	// 	game->rayDown = 0;
	// }
	// else if (game->rotationAngle > 180 && game->rotationAngle < 360) {
	// 	game->rayDown = 1;
	// 	game->rayUp = 0;
	// }
	// if (game->rotationAngle > 90 && game->rotationAngle < 270) {
	// 	game->rayLeft = 1;
	// 	game->rayRight = 0;
	// }
	// else if ((game->rotationAngle > 0 && game->rotationAngle < 90 )||  ( game->rotationAngle > 270 && game->rotationAngle < 360)) {
	// 	game->rayRight = 1;
	// 	game->rayLeft = 0;
	// }

	// printf("Up : %d\n", game->rayUp);
	// printf("rayDown : %d\n", game->rayDown);
	// printf("rayLeft : %d\n", game->rayLeft);
	// printf("rayRight : %d\n", game->rayRight);

}

void rayCasting(t_game *game)
{
	game->rayAngle = game->rotationAngle - game->halfFov; // needed for drawing next ray
	printf("%d\n", game->rotationAngle);

	game->rayAngleY = -sin(degreeToRadian(game->rayAngle));
	game->rayAngleX = cos(degreeToRadian(game->rayAngle));
	// printf("game->rayAngleY %lf\n", game->rayAngleY);
	// 	printf("game->rayAngleX %lf\n", game->rayAngleX);
	int floorY = 0, floorX = 0, wallHit = 0;


	double yintersec = 0, xintersec = 0; // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall
	int ystep = 0, xstep = 0;  // deltaY  // deltaX

	// RAY DIRECTION UP DOWN LEFT RIGHT
	// init the down up left right here
	if (game->rotationAngle > 359)
		game->rotationAngle -= 360;
	if (game->rotationAngle < 0)
		game->rotationAngle = 0;
	// printf("%d\n", game->rotationAngle);
	if (game->rotationAngle >= 0 && game->rotationAngle < 180) {
		game->rayUp = 1;
		game->rayDown = 0;
	}
	else if (game->rotationAngle >= 180 && game->rotationAngle < 360) {
		game->rayDown = 1;
		game->rayUp = 0;
	}
	if (game->rotationAngle > 90 && game->rotationAngle < 270) {
		game->rayLeft = 1;
		game->rayRight = 0;
	}
	else if ((game->rotationAngle > 0 && game->rotationAngle < 90 )||  ( game->rotationAngle > 270 && game->rotationAngle < 360)) {
		game->rayRight = 1;
		game->rayLeft = 0;
	}

	// !1
	yintersec = (game->posY / SQUARE_SIZE) * SQUARE_SIZE; // floor it
	if (game->rayDown) // !!!!!!!!!!!!!!!!1!!!!!!!!!!!!!!!!!
		yintersec += SQUARE_SIZE;
	xintersec = (game->posX + (yintersec - game->posY) / tan(degreeToRadian(game->rayAngle)));

	// !2
	ystep = SQUARE_SIZE;
	if (game->rayUp)
		ystep *= -1;

	// !3
	xstep = ystep / tan(degreeToRadian(game->rayAngle));
	// if (game->rayLeft && xstep > 0)
	// 	xstep *= -1;
	// if (game->rayRight && xstep < 0)
	// 	xstep *= -1;

	double nextY = yintersec, nextX = xintersec; // first nextY = yintersec; nextX = xintersec; then increment the value with ystep and xstep in the while
	if (game->rayUp)
		nextY--; // substract a pixel to check if nextY is in the wall
	while (!wallHit)  // checking Horizontal intersection – the y-axis
	{
		if (nextY < 0 || nextY >= game->WINDOW_HEIGHT)
			break;
		if (nextX < 0 || nextX > game->WINDOW_WIDTH)
			break;

		floorY = floor(nextY) / SQUARE_SIZE;
		floorX = floor(nextX) / SQUARE_SIZE;

		if (k) {
			printf("floorY %d\n", floorY);
			printf("floorX %d\n", floorX);
			k = 0;
		}
		if (game->map[floorY][floorX] == '1')
			break;



		nextY += ystep;
		nextX += xstep;
	}



	// // checking Vertical intersection – the y-axis

	// wallHit = 0;

















	nextY++;
	printf("here\n");
	printf("nextY : %lf\n", nextY);
	printf("nextX : %lf\n", nextX);
	drawLine(game, game->posY, game->posX, nextY, nextX, 0xcfc08);
	printf("here2\n");

}

int render(t_game *game)
{
	// drawWall(game);
	// drawRect(game, game->posY, game->posX, 10, 10, 0xcfc08);
	// rayCasting(game);

	return 0;
}
