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
		if (out_of_container_borders(game))
			break;
		// drawRect(game, (int) yinter, (int) xinter, 5, 5, 0xcfc08);
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)][(int)floor(game->xinter / SQUARE_SIZE)] == '1')
			break;
		game->yinter += game->ystep;
		game->xinter += game->xstep;
	}
	// if (game->rayUp)
	// 	game->yinter++;
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
		if (out_of_container_borders(game))
			break;
		// drawRect(game, (int) yinter, (int) xinter, 5, 5, 0xff3399);
		if (game->map[(int)floor(game->yinter / SQUARE_SIZE)][(int)floor(game->xinter / SQUARE_SIZE)] == '1')
			break;
		game->xinter += game->xstep;
		game->yinter += game->ystep;
	}
	// if (game->rayLeft)
	// 	game->xinter++;

	game->verticalWallHitY = game->yinter;
	game->verticalWallHitX = game->xinter;
}

void init_vars_to_zero(t_game *game)
{
	// deltaY  // deltaX | // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall
	game->yinter = 0;
	game->xinter = 0;
	game->ystep = 0;
	game->xstep = 0;
}

int out_of_container_borders(t_game *game)
{
	if (game->yinter < 0 || game->yinter >= game->windowHeight)
		return 1;
	if (game->xinter < 0 || game->xinter > game->windowWidth)
		return 1;
	return 0;
}

void old(t_game *game)
{

	double rayX = game->posX;
	double rayY = game->posY;
	int floorY;
	int floorX;
	int wallHit = 0;
	while (!wallHit)
	{
		rayX += game->dirX;
		rayY += game->dirY;
		floorY = floor(rayY);
		floorX = floor(rayX);

		if (game->map[floorY / SQUARE_SIZE][floorX / SQUARE_SIZE] == '1')
			break;
	}
	game->wallHitX = floorX;
	game->wallHitY = floorY;
}

void drawRect(t_game *game, int startX, int startY, int sizeX, int sizeY, int color)
{
	int y = 0;
	int x;
	while (y < sizeY)
	{
		x = 0;
		while (x < sizeX)
		{
			edit_pixel(game->imgData->frame_addr, game->imgData->sLine, game->imgData->bpp, x + startX, y + startY, color);
			x++;
		}
		y++;
	}
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

	game->distanceToProjectedWall = (game->windowHeight / 2) / tan(degreeToRadian(game->halfFov));

	int wallTopPixel;
	int wallBottomPixel;
	int floor;
	int ceil;
	int coorectDistance;
	int x = -1;
	while (++x < game->windowWidth)
	{
		checkHorizontalCollision(game);
		checkVerticalCollision(game);
		verticalDistance = distance(game->posX, game->posY, game->verticalWallHitX, game->verticalWallHitY);
		horizontalDistance = distance(game->posX, game->posY, game->horizontalWallHitX, game->horizontalWallHitY);
		if (horizontalDistance < verticalDistance)
			actualDistanceToWall = horizontalDistance;
		else
			actualDistanceToWall = verticalDistance;

		// !!!!!fishe eye
		coorectDistance = actualDistanceToWall * (cos(degreeToRadian(game->rayAngle - game->playerAngle)));

		// !!!!! distance To Projectddd Wall
		game->projectedWallHeight = (double)(SQUARE_HEIGHT * game->distanceToProjectedWall) / coorectDistance;
		if (game->projectedWallHeight > game->windowHeight) game->projectedWallHeight = game->windowHeight;

		wallTopPixel = (game->windowHeight / 2) - (game->projectedWallHeight / 2); // wallHeight drawing start postion on the y-axis
		wallBottomPixel = (game->windowHeight/2) + (game->projectedWallHeight / 2);
		floor = game->windowHeight - wallBottomPixel;

		drawRect(game, x, 0, 1, wallTopPixel, 0x454745); // draw the ceil
		drawRect(game, x, wallTopPixel, 1, game->projectedWallHeight, 0xffffff);
		drawRect(game, x, wallBottomPixel, 1, floor, 0x808a83); // draw the floor

		game->rayAngle += game->rayAngleIncrement; // needed for drawing next ray // if it goes over 360, will reset to 0 + rayAngle
		if (game->rayAngle > 360)
			game->rayAngle = 360 - game->rayAngle;
		// correct_angle(); make this
	}
}

int render(t_game *game)
{
	// draw(game); // !! will get removed and used the render function

	return 0;
}
