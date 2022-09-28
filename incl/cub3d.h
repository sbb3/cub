/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:17:38 by adouib            #+#    #+#             */
/*   Updated: 2022/09/16 15:15:41 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/time.h>

#define ESC_KEY 53
#define W_KEY 13
#define S_KEY 1
#define A_KEY 2
#define D_KEY 0
#define LEFT_KEY 124
#define RIGHT_KEY 123

#define COLOR 0x0000FF

#define SQUARE_SIZE 48
#define MINIMAP_SIZE 10

#define SQUARE_WIDTH 48
#define SQUARE_HEIGHT 48

#define BUFFER_SIZE 1
#define degreeToRadian(angleInDegree) ((angleInDegree) * (M_PI / 180))

typedef struct s_img_data
{
	int bpp;
	int sLine;
	int endn;
	char *frame_addr;
	void *frame;
} t_img_data;

typedef struct s_game
{
	t_img_data *imgData;

	void *mlx;
	void *win;
	int img_width;
	int img_height;

	int map_fd;
	char **map;
	char *line;
	char *backup;
	int mapWidth;
	int mapHeight;
	int windowWidth;
	int windowHeight;
	int halfWidth;
	int halfHeight;

	int posX;
	int posY;
	double dirX;	 // 1
	double dirY;	 // 0
	int playerAngle; // player angle
	int fov;		 // 60 // filed of view
	int halfFov;
	double movementSpeed;
	double rotation;


	double rayAngle;
	double rayAngleY;
	double rayAngleX;
	double rayAngleIncrement;
	int rayUp;
	int rayDown;
	int rayLeft;
	int rayRight;

	int wallHit;
	double horizontalWallHitX;
	double horizontalWallHitY;
	double verticalWallHitX;
	double verticalWallHitY;

	double xinter;
	double yinter;
	double xstep;
	double ystep;


	double plane_wall_height;
	double distance_to_plane_wall;
	int rays_count;


	int minimapWidth;
	int minimapHeight;


	double scale_factor_width;
	double scale_factor_height;


	// int
} t_game;

// typedef struct s_player {

// }

char *get_next_line(int fd);
char *ft_strjoin(char *backup, char *file_buffer);
char *ft_strdup(char *s);
int search_newline(char *s, char c);
int ft_slen(char *s);

void parser(const char *av[], t_game *game);
char **map_read(const char *av[], t_game *game);
void check_map_extension(const char *av[]);
int mapWidth(char *s);
int mapHeight(char *s[]);
char **ft_split(char *s, char c);
int ft_strrstr(const char *haystack, const char *needle, int n);
int ft_strchr(char *s, char c);
int ft_strlen(const char *s);

int render(t_game *game);
void draw_wall_floor(t_game *game, char c, int x, int y);
void throw_rays(t_game *game, int y, int x);
void draw_exit(t_game *game);
int keyPressed(int keycode, t_game *game);

void quit(t_game *game, char *s);
void deleteImage(t_game *game);
int red_cross_quit(t_game *game);
char **free_map(char **token);
void drawWalls(t_game *game);
void edit_pixel(char *frame_addr, int size_line, int bits_per_pixel, int x, int y, int color);
int distance(int startX, int startY, int endX, int endY);

void *ft_calloc(size_t count, size_t size);
void exit_if_null(void *p, char *message);
t_game *init(const char *av[]);
void drawLinePlayer(t_game *game, int startY, int startX, int color);
void drawLine(t_game *game, int startX, int startY, int endX, int endY, int color);

void drawRect(t_game *game, int startX, int startY , int sizeX, int sizeY, int color);
void rayCasting(t_game *game);
void checkRayDirection(t_game *game);
void fix_angle(t_game *game, char c);

void checkHorizontalCollision(t_game *game);
void checkVerticalCollision(t_game *game);
t_img_data *createImage(t_game *game);
void mlxInit(t_game *game);
void draw(t_game *game);
int	out_of_container_borders(t_game *game);
void	init_vars_to_zero(t_game *game);
void	minimap(t_game *game);
int	scaleDownWidth(t_game *game, int coordinateX);
int	scaleDownHeight(t_game *game, int coordinateY);




void	draw_test_minimap(t_game *game);
void	test_minimap(t_game *game);
void drawRectMinimap(char *frame_addr,int bpp, int sLine, int startX, int startY , int sizeX, int sizeY, int color);


#endif
