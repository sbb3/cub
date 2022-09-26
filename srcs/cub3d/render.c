#include "../../incl/cub3d.h"

void checkRayDirection(t_game *game)
{
	if (game->rayAngle >= 0 && game->rayAngle < 180)
	{
		game->rayUp = 1;
		game->rayDown = 0;
	}
	else if (game->rayAngle >= 180 && game->rayAngle < 360)
	{
		game->rayDown = 1;
		game->rayUp = 0;
	}
	if (game->rayAngle > 90 && game->rayAngle < 270)
	{
		game->rayLeft = 1;
		game->rayRight = 0;
	}
	else if ((game->rayAngle > 0 && game->rayAngle < 90) || (game->rayAngle > 270 && game->rayAngle < 360))
	{
		game->rayRight = 1;
		game->rayLeft = 0;
	}
}

int distance(int startX, int startY, int endX, int endY)
{
	return (sqrt(pow((abs(endX - startX)), 2) + pow((abs(endY - startY)), 2)));
}

void edit_pixel(char *frame_addr, int sLine, int bpp, int x, int y, int color)
{
	char *color_pixel = frame_addr + ((y * sLine) + (x * (bpp / 8)));
	*(int *)color_pixel = color;
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

// void	deleteImage(t_game *game) {}

void drawLine(t_game *game, int startX, int startY, int endX, int endY, int color)
{
	// pythaghors equation
	int pixelsCount = distance(startX, startY, endX, endY); // number of pixels will be in the line or the distance ! https://www.mathsisfun.com/algebra/distance-2-points.html
	double pixelX = startX;
	double pixelY = startY;

	while (pixelsCount)
	{
		edit_pixel(game->imgData->frame_addr, game->imgData->sLine, game->imgData->bpp, pixelX, pixelY, color);
		pixelX += game->rayAngleX; // dirX = direction, default to 0, range  [ -1 < 0 < 1 ]
		pixelY += game->rayAngleY; // dirY = direction, default to -1, range [ -1 < 0 < 1 ]
		pixelsCount--;
	}
}

void checkHorizontalCollision(t_game *game)
{
	int wallHit = 0;
	double yintersec = 0, xintersec = 0, ystep = 0, xstep = 0; // deltaY  // deltaX | // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall
	game->rayAngleX = cos(degreeToRadian(game->rayAngle));
	game->rayAngleY = -sin(degreeToRadian(game->rayAngle));
	checkRayDirection(game);
	yintersec = (game->posY / SQUARE_SIZE) * SQUARE_SIZE; // floor it
	if (game->rayDown)
		yintersec += SQUARE_SIZE;
	xintersec = (game->posX + ((game->posY - yintersec) / tan(degreeToRadian(game->rayAngle)))); // absolute (yinter - posY)
	ystep = SQUARE_SIZE;
	if (game->rayUp)
		ystep *= -1;
	xstep = SQUARE_SIZE / tan(degreeToRadian(game->rayAngle));
	if (game->rayLeft && xstep > 0)
		xstep *= -1; // xstep on left down side will be positive so we turn it to negative same as the left up side, is already negative
	if (game->rayRight && xstep < 0)
		xstep *= -1; // xstep on right down side will be negative so we turn it to positive same as the right up side, is already positive
	if (game->rayUp)
		yintersec--; // substract a pixel to check if nextY is in the wall
	while (!wallHit) // checking Horizontal intersection – the y-axis
	{
		if (yintersec < 0 || yintersec >= game->windowHeight)
			break;
		if (xintersec < 0 || xintersec > game->windowWidth)
			break;
		// drawRect(game, (int) yintersec, (int) xintersec, 5, 5, 0xcfc08);
		if (game->map[(int)floor(yintersec / SQUARE_SIZE)][(int)floor(xintersec / SQUARE_SIZE)] == '1')
			break;
		yintersec += ystep;
		xintersec += xstep;
	}
	game->horizontalWallHitY = yintersec;
	game->horizontalWallHitX = xintersec;
}

void checkVerticalCollision(t_game *game)
{
	int wallHit = 0;
	double yintersec = 0, xintersec = 0, ystep = 0, xstep = 0; // deltaY  // deltaX | // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall

	game->rayAngleX = cos(degreeToRadian(game->rayAngle));
	game->rayAngleY = -sin(degreeToRadian(game->rayAngle));
	checkRayDirection(game);
	xintersec = (game->posX / SQUARE_SIZE) * SQUARE_SIZE; // floor it
	if (game->rayRight)
		xintersec += SQUARE_SIZE;
	yintersec = (game->posY + ((game->posX - xintersec) * tan(degreeToRadian(game->rayAngle))));
	xstep = SQUARE_SIZE;
	if (game->rayLeft)
		xstep *= -1;
	ystep = SQUARE_SIZE * tan(degreeToRadian(game->rayAngle));
	if (game->rayUp && ystep > 0)
		ystep *= -1;
	if (game->rayDown && ystep < 0)
		ystep *= -1;
	if (game->rayLeft)
		xintersec--;
	while (!wallHit) // checking Horizontal intersection – the y-axis
	{
		if (yintersec < 0 || yintersec >= game->windowHeight)
			break;
		if (xintersec < 0 || xintersec > game->windowWidth)
			break;
		// drawRect(game, (int) yintersec, (int) xintersec, 5, 5, 0xff3399);
		if (game->map[(int)floor(yintersec / SQUARE_SIZE)][(int)floor(xintersec / SQUARE_SIZE)] == '1')
			break;
		xintersec += xstep;
		yintersec += ystep;
	}
	game->verticalWallHitY = yintersec;
	game->verticalWallHitX = xintersec;
}

void rayCasting(t_game *game)
{
	system("clear");
	double wallHitY = 0, wallHitX = 0; // deltaY  // deltaX | // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall
	int horizontalDistance = 0, verticalDistance = 0;
	game->rayAngle = (game->playerAngle - game->halfFov) % 360; // needed for drawing next ray // if it goes over 360, will reset to 0
	if (game->rayAngle < 0)
		game->rayAngle = 360 + game->rayAngle;

	int i = -1;
	while (++i < game->windowWidth)
	{
		checkHorizontalCollision(game);
		checkVerticalCollision(game);
		verticalDistance = distance(game->posX, game->posY, game->verticalWallHitX, game->verticalWallHitY);
		horizontalDistance = distance(game->posX, game->posY, game->horizontalWallHitX, game->horizontalWallHitY);


		if (horizontalDistance < verticalDistance)
		{
			wallHitX = game->horizontalWallHitX;
			wallHitY = game->horizontalWallHitY;
		}
		else
		{
			wallHitX = game->verticalWallHitX;
			wallHitY = game->verticalWallHitY;
		}

		drawLine(game, game->posX, game->posY, (int)wallHitX, (int)wallHitY, 0xcfc08);
		game->rayAngle += game->rayAngleIncrement; // needed for drawing next ray // if it goes over 360, will reset to 0
		if (game->rayAngle > 360)
			game->rayAngle = 360 - game->rayAngle;
		// correct_angle(); make this
	}
}

int render(t_game *game)
{
	// drawWalls(game);
	// rayCasting(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->imgData->frame, 0, 0);

	return 0;
}
