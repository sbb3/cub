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

void draw_ceiling_floor(t_game *game, int startX, int startY, int endY, int color)
{
	// draw_ceiling : starting from 0
	// draw_floor : starting from wallBottomPixel
	// going by x and drawing each y pixel
	while (startY < endY)
	{
		edit_pixel(game->globalImgData->frame_addr, game->globalImgData->line_bytes, game->globalImgData->bpp, startX, startY, color);
		startY++;
	}
}

void rayCasting(t_game *game)
{
	int actualDistanceToWall;
	// system("clear");
	// double wallHitY = 0, wallHitX = 0; // deltaY  // deltaX | // first check if these coordinates are at wall, else increment them with ystep and xstep till u find a wall
	int horizontalDistance = 0, verticalDistance = 0;
	game->rayAngle = (game->playerAngle - game->halfFov) % 360; // needed for drawing next ray // if it goes over 360, will reset to 0
	if (game->rayAngle < 0)
		game->rayAngle = 360 + game->rayAngle;

	game->distanceToProjectedWall = (game->windowHeight / 2) / tan(degreeToRadian(game->halfFov));
	unsigned int color;
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
		{
			game->horizontalHit = 1;
			game->wallHitX = game->horizontalWallHitX;
			game->wallHitY = game->horizontalWallHitY;
			actualDistanceToWall = horizontalDistance;
		}
		else
		{
			game->horizontalHit = 0;
			game->wallHitX = game->verticalWallHitX;
			game->wallHitY = game->verticalWallHitY;
			actualDistanceToWall = verticalDistance;
		}

		// !!!!!fishe eye
		coorectDistance = actualDistanceToWall * (cos(degreeToRadian(game->rayAngle - game->playerAngle)));

		// !!!!! distance To Projectddd Wall
		game->projectedWallHeight = (double)(SQUARE_HEIGHT * game->distanceToProjectedWall) / coorectDistance;
		if (game->projectedWallHeight > game->windowHeight)
			game->projectedWallHeight = game->windowHeight;

		wallTopPixel = (game->windowHeight / 2) - (game->projectedWallHeight / 2); // wallHeight drawing start postion on the y-axis
		if (wallTopPixel < 0)
			wallTopPixel = 0;
		wallBottomPixel = (game->windowHeight / 2) + (game->projectedWallHeight / 2);
		if (wallBottomPixel > game->windowHeight)
			wallBottomPixel = game->windowHeight;

		if (game->horizontalHit)
			game->textureOffsetX = game->wallHitX % SQUARE_SIZE;
		else
			game->textureOffsetX = game->wallHitY % SQUARE_SIZE;

		// draw_ceiling_floor(game, x, 0, wallTopPixel, 0x454745); // draw the ceil
		floor = game->windowHeight;
		draw_ceiling_floor(game, x, wallBottomPixel, floor, 0x808a83); // draw the floor

		game->scaling_factor = (double)TEXTURE_HEIGHT / game->projectedWallHeight; // projectedWallHeight
		draw_texture_colors_on_walls(game, x, wallTopPixel, wallBottomPixel);

		game->rayAngle += game->rayAngleIncrement; // needed for drawing next ray // if it goes over 360, will reset to 0 + rayAngle
		if (game->rayAngle > 360)
			game->rayAngle = 360 - game->rayAngle;
		// correct_angle(); make this
	}

	mlx_put_image_to_window(game->mlx, game->win, game->globalImgData->frame, 0, 0);
}

unsigned int get_the_color_from_texture(t_game *game) // main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
{
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (game->textureOffsetY * game->texture_data->line_bytes) + (game->textureOffsetX * (game->texture_data->bpp / 8));
	color_pixel = game->texture_data->frame_addr + pixelOffset;
	return (*(unsigned int *)color_pixel);
}

void set_the_texture_color_on_walls(t_game *game, int x, int y, int color)
{
	// color the pixel on the x, y coordinates
	int pixelOffset; // pixeloffset where the pixel laying down
	char *color_pixel;

	pixelOffset = (y * game->globalImgData->line_bytes) + (x * game->globalImgData->bpp / 8); // * 4 (4 bytes) // convert from bits to bytes
	color_pixel = game->globalImgData->frame_addr + pixelOffset;							  // points to the first byte in the pixel (4 bytes)
	*(unsigned int *)color_pixel = game->texture_data->txtcolor;							  // main reason for doing the unsigned int, is there is no sign bit as in int and the guarantee size 4 bytes
																							  // write the texture_color on the main image
}

void draw_texture_colors_on_walls(t_game *game, int startX, int wallTopPixel, int wallBottomPixel) // sizeX or width of the strip(column) will be 1, but since it is 1, there is no need to specify it here
{
	int color;
	int y;
	y = wallTopPixel;
	while (y < wallBottomPixel) // start drawing from the wallTopPixel till wallBottomPixel , this distance is equal to projectedWallHeight
	{
		// calculate the offsetY
		game->textureOffsetY = (y - wallTopPixel) * game->scaling_factor; // what pixel color to pick from the texture
		game->texture_data->txtcolor = get_the_color_from_texture(game);  // hex color not rgb // the texture pixel color that will drawn on the globalImage
		set_the_texture_color_on_walls(game, startX, y, color);
		y++;
	}
}
