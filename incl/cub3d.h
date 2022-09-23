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
#define A_KEY 0
#define D_KEY 2
#define LEFT_KEY 123
#define RIGHT_KEY 124

#define COLOR 0x0000FF

// #define WINDOW_WIDTH 864
// #define WINDOW_HEIGHT 720

#define IMG_WIDTH 48
#define IMG_HEIGHT 48

#define BUFFER_SIZE 1
#define degreeToRadian(angleInDegree) ((angleInDegree) * (M_PI / 180))

typedef struct s_img
{
	int bits_per_pixel;
	int size_line;
	int endian;
	char *frame_addr;
	void *frame;
} img_data;

typedef struct s_game
{
	img_data *img_data;

	void *mlx;
	void *win;
	void *img;
	int img_width;
	int img_height;

	int map_fd;
	char **map;
	char *line;
	char *backup;
	int map_width;
	int map_height;

	int posX;
	int posY;
	double dirX; // 1
	double dirY; // 0
	int angle;	 // player angle
	int fov;	 // 60 // filed of view

	double movementSpeed;
	double rotation;
	int halfWidth;
	int halfHeight;
	void *frame_img;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
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
void check_rectangle(char *map[]);
void check_walls(char *map[], t_game *game);
void check_characters(char *map[], t_game *game);
int map_width(char *s);
int map_height(char *s[]);
int search_map(char *s, char c);
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
void free_image(t_game *game);
int red_cross_quit(t_game *game);
char **free_map(char **token);
int intersection(t_game *game, double x1, double y1, double x2, double y2);
void drawWall(t_game *game);
void edit_pixel(char *frame_addr, int size_line, int bits_per_pixel, int x, int y, int color);
int distance(int startY, int startX, int endY, int endX);
void *ft_calloc(size_t count, size_t size);
void exit_if_null(void *p, char *message);
t_game * init(const char *av[]);


#endif
