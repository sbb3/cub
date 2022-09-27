#include "../../incl/cub3d.h"

int distance(int startX, int startY, int endX, int endY)
{
	return (sqrt(pow((abs(endX - startX)), 2) + pow((abs(endY - startY)), 2)));
}

void checkRayDirection(t_game *game)
{
	if (game->rayAngle >= 0 && game->rayAngle <= 180)
	{
		game->rayUp = 1;
		game->rayDown = 0;
	}
	else if (game->rayAngle > 180 && game->rayAngle <= 360)
	{
		game->rayDown = 1;
		game->rayUp = 0;
	}
	if (game->rayAngle >= 90 && game->rayAngle <= 270)
	{
		game->rayLeft = 1;
		game->rayRight = 0;
	}
	else if ((game->rayAngle >= 0 && game->rayAngle < 90) || (game->rayAngle > 270 && game->rayAngle <= 360))
	{
		game->rayRight = 1;
		game->rayLeft = 0;
	}
}

void edit_pixel(char *frame_addr, int sLine, int bpp, int x, int y, int color)
{
	char *color_pixel = frame_addr + ((y * sLine) + (x * (bpp / 8)));
	*(int *)color_pixel = color;
}


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
	init_vars_to_zero(game);
	game->rayAngleX = cos(degreeToRadian(game->rayAngle));
	game->rayAngleY = -sin(degreeToRadian(game->rayAngle));
	checkRayDirection(game);
	game->yinter = (game->posY / SQUARE_SIZE) * SQUARE_SIZE; // floor it
	if (game->rayDown)
		game->yinter += SQUARE_SIZE;
	if (tan(degreeToRadian(game->rayAngle) == 0)) // !!!!1 inf or nan
		game->rayAngle -= degreeToRadian(1);
	game->xinter = (game->posX + ((game->posY - game->yinter) / tan(degreeToRadian(game->rayAngle)))); // absolute (yinter - posY)
	game->ystep = SQUARE_SIZE;
	if (game->rayUp)
		game->ystep *= -1;
	game->xstep = SQUARE_SIZE / tan(degreeToRadian(game->rayAngle));
	if (game->rayLeft && game->xstep > 0)
		game->xstep *= -1; // xstep on left down side will be positive so we turn it to negative same as the left up side, is already negative
	if (game->rayRight && game->xstep < 0)
		game->xstep *= -1; // xstep on right down side will be negative so we turn it to positive same as the right up side, is already positive
	if (game->rayUp)
		game->yinter--; // substract a pixel to check if nextY is in the wall
	game->wallHit = 0;
	while (!game->wallHit) // checking Horizontal intersection – the y-axis
	{
		if(out_of_container_borders(game))
			break;
		// drawRect(game, (int) yinter, (int) xinter, 5, 5, 0xcfc08);
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)][(int)floor(game->xinter / SQUARE_SIZE)] == '1')
			break;
		game->yinter += game->ystep;
		game->xinter += game->xstep;
	}
	game->horizontalWallHitY = game->yinter;
	game->horizontalWallHitX = game->xinter;
}

void checkVerticalCollision(t_game *game)
{
	init_vars_to_zero(game);

	game->rayAngleX = cos(degreeToRadian(game->rayAngle));
	game->rayAngleY = -sin(degreeToRadian(game->rayAngle));
	checkRayDirection(game);
	game->xinter = (game->posX / SQUARE_SIZE) * SQUARE_SIZE; // floor it
	if (game->rayRight)
		game->xinter += SQUARE_SIZE;
	game->yinter = (game->posY + ((game->posX - game->xinter) * tan(degreeToRadian(game->rayAngle))));
	game->xstep = SQUARE_SIZE;
	if (game->rayLeft)
		game->xstep *= -1;
	game->ystep = SQUARE_SIZE * tan(degreeToRadian(game->rayAngle));
	if (game->rayUp && game->ystep > 0)
		game->ystep *= -1;
	if (game->rayDown && game->ystep < 0)
		game->ystep *= -1;
	if (game->rayLeft)
		game->xinter--;
	game->wallHit = 0;
	while (!game->wallHit) // checking Horizontal intersection – the y-axis
	{
		if(out_of_container_borders(game))
			break;
		// drawRect(game, (int) yinter, (int) xinter, 5, 5, 0xff3399);
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)][(int)floor(game->xinter / SQUARE_SIZE)] == '1')
			break;
		game->xinter += game->xstep;
		game->yinter += game->ystep;
	}
	game->verticalWallHitY = game->yinter;
	game->verticalWallHitX = game->xinter;
}

void	init_vars_to_zero(t_game *game)
{
	// deltaY  // deltaX | // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall
	game->yinter = 0;
	game->xinter = 0;
	game->ystep = 0;
	game->xstep = 0;
}

int	out_of_container_borders(t_game *game)
{
	if (game->yinter < 0 || game->yinter >= game->windowHeight)
		return 1;
	if (game->xinter < 0 || game->xinter > game->windowWidth)
		return 1;
	return 0;
}


void rayCasting(t_game *game)
{
	int actualDistanceToWall;
	// system("clear");
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
			actualDistanceToWall = horizontalDistance;
		}
		else
		{
			wallHitX = game->verticalWallHitX;
			wallHitY = game->verticalWallHitY;
			actualDistanceToWall = verticalDistance;

		}

		game->distance_to_plane_wall = (game->windowWidth / 2) / tan(degreeToRadian(game->halfFov));
		game->plane_wall_height = (SQUARE_HEIGHT * game->distance_to_plane_wall) / actualDistanceToWall;

		// drawLine(game, game->posX, game->posY, (int)wallHitX, (int)wallHitY, 0xcfc08);
		drawRect(game, i, (game->windowHeight/2) - (game->plane_wall_height/2), 1, game->plane_wall_height, 0xffffff);


		game->rayAngle += game->rayAngleIncrement; // needed for drawing next ray // if it goes over 360, will reset to 0 + rayAngle
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
