/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/10/22 19:33:23 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
#define RENDER_H

#include <mlx.h>
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/time.h>

#define NORTH_TEXTURE "./images/purplestone.xpm"
#define SOUTH_TEXTURE "./images/bluestone.xpm"
#define WEST_TEXTURE "./images/greystone.xpm"
#define EAST_TEXTURE "./images/redbrick.xpm"

#define ESC_KEY 53
#define W_KEY 13
#define S_KEY 1
#define A_KEY 0
#define D_KEY 2
#define LEFT_KEY 123
#define RIGHT_KEY 124
#define SQUARE_SIZE 64
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define MINIMAP_SIZE 10

#define SQUARE_WIDTH 64
#define SQUARE_HEIGHT 64

#define degreeToRadian(angleInDegree) ((angleInDegree)*M_PI / 180)

#define SPEED 15
#define ROTATION 6
#define FOV 60			   // field of view of the player
#define HALF_FOV (FOV / 2) // half of view of the player

#define WINDOW_WIDTH (SQUARE_WIDTH * game->map_width)
#define WINDOW_HEIGHT (SQUARE_WIDTH * game->map_height)

#define HALF_WINDOW_WIDTH (WINDOW_WIDTH / 2)
#define HALF_WINDOW_HEIGHT (WINDOW_HEIGHT / 2)

#define RAYS WINDOW_WIDTH

typedef struct n_texture
{
	void *frame;
	char *frame_addr;
	int bpp;
	int line_bytes;
	int endn;
	unsigned int texture_color;
	int w;
	int h;
} n_texture;

typedef struct s_texture
{
	void *frame;
	char *frame_addr;
	int bpp;
	int line_bytes;
	int endn;
	unsigned int texture_color;
	int w;
	int h;
} s_texture;

typedef struct w_texture
{
	void *frame;
	char *frame_addr;
	int bpp;
	int line_bytes;
	int endn;
	unsigned int texture_color;
	int w;
	int h;
} w_texture;

typedef struct e_texture
{
	void *frame;
	char *frame_addr;
	int bpp;
	int line_bytes;
	int endn;
	unsigned int texture_color;
	int w;
	int h;
} e_texture;

typedef struct s_global_image
{
	void *frame;
	char *frame_addr;
	int bpp;
	int line_bytes;
	int endn;
} t_global_image;

typedef struct s_ray
{

} t_ray;

typedef struct s_player
{

} t_player;

typedef struct s_wall
{

} t_wall;

typedef struct s_game
{
	t_global_image *global_img;
	n_texture *n_t_data;
	s_texture *s_t_data;
	w_texture *w_t_data;
	e_texture *e_t_data;

	void *mlx;
	void *win;
	int img_width;
	int img_height;
	int map_fd;
	char **map;
	char *line;
	char *backup;
	int map_width;
	int map_height;

	int window_width;
	int window_height;
	int half_width;
	int half_height;

	int pos_x;
	int pos_y;
	float pdir_x;		// 1
	float pdir_y;		// 0
	float player_angle; // player angle

	float ray_angle;
	float ray_angle_increment;
	int ray_up;
	int ray_down;
	int ray_left;
	int ray_right;

	int is_north;
	int is_south;
	int is_west;
	int is_east;

	float horizontal_wall_hit_x;
	float horizontal_wall_hit_y;
	float vertical_wall_hit_x;
	float vertical_wall_hit_y;

	float xinter;
	float yinter;
	float xstep;
	float ystep;

	float projected_wall_height;
	float distance_to_projected_wall;
	int rays_count;

	int minimap_width;
	int minimap_height;

	int wall_hit;
	float wall_hit_x;
	float wall_hit_y;

	int horizontal_Hit;
	int texture_offset_x;
	int texture_offset_y;

	// raycasting variables
	float distorted_ray_distance_to_wall;
	float correct_ray_distance;

	float horizontal_distance_to_wall;
	float vertical_distance_to_wall;

	int wall_top_pixel;
	int wall_bottom_pixel;

	double test;
	double test2;

} t_game;

void old(t_game *game);

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

// int drawTexture(t_game *game);
void draw_wall_floor(t_game *game, char c, int x, int y);
void throw_rays(t_game *game, int y, int x);
void draw_exit(t_game *game);
int movements(int keycode, t_game *game);

void quit(t_game *game, char *s);
void delete_global_image_then_clear_window(t_game *game);
int red_cross_quit(t_game *game);
char **free_map(char **token);
void draw_minimap_walls(t_game *game);
void coloring_pixel(t_game *game, int x, int y, int color);
float distance(int startX, int startY, int endX, int endY);

void *ft_calloc(size_t count, size_t size);
void exit_if_null(void *p, char *message);
t_game *init_variables(const char *av[]);
void drawLinePlayer(t_game *game, int startY, int startX, int color);
void drawLine(t_game *game, int startX, int startY, int endX, int endY, int color);

void draw_ceiling_floor(t_game *game, int startX, int startY, int sizeY, int color);
void raycasting(t_game *game);
void check_ray_direction(t_game *game);
void fix_angle(t_game *game, char c);

void ray_wall_collision_horizontally(t_game *game);
void ray_wall_collision_vertically(t_game *game);
t_global_image *createGlobalImage(t_game *game);
void draw(t_game *game);
int out_of_container_width_and_height(t_game *game);
void reset_vars_to_zero(t_game *game);
void minimap(t_game *game);
int scale_down(t_game *game, int minimap_size, int window_size, int coordinate);

void drawRectMinimap(char *frame_addr, int bpp, int sLine, int startX, int startY, int sizeX, int sizeY, int color);
unsigned int get_the_color_from_north_texture(t_game *game);
void draw_texture_colors_on_walls(t_game *game, int startX, int wall_top_pixel, int wall_bottom_pixel);
n_texture *createNorthTextureImage(t_game *game);
void set_the_texture_color_on_walls(t_game *game, int x, int y, unsigned int color);
void edit_pixel(t_game *game, int startX, int startY, int sizeX, int sizeY, int color);
void draw_floor(t_game *game, int startX, int startY, int endX, int endY, int color);
void correct_player_angle(t_game *game);
void correct_ray_angle(t_game *game);
void calculations(t_game *game);
void get_the_short_distance(t_game *game);
void get_projected_wall_height(t_game *game);
void get_wall_top_bottom_pixels(t_game *game);
void intersections_and_steps_vertically(t_game *game);
void looking_for_wall_coordinates_vertically(t_game *game);
void intersections_and_steps_horizontally(t_game *game);
void looking_for_wall_coordinates_horizontally(t_game *game);
void do_init(t_game *game);
void do_init_more(t_game *game);
void draw_minimap_player(t_game *game);
void re_draw(t_game *game);
s_texture *createSouthTextureImage(t_game *game);
w_texture *createWestTextureImage(t_game *game);
e_texture *createEastTextureImage(t_game *game);
unsigned int get_the_color_from_south_texture(t_game *game);
unsigned int get_the_color_from_west_texture(t_game *game);
unsigned int get_the_color_from_east_texture(t_game *game);
void ray_direction(t_game *game);
void free_all(t_game *game);
void redraw(t_game *game);
void move_down(t_game *game);
void move_left(t_game *game);
void move_right(t_game *game);
void rotate(t_game *game, char c);
void correct_angle(int *angle);
void move_up_down(t_game *game, char c);
void move_left_right(t_game *game, char c);
void rotate(t_game *game, char c);

// void init_variables_and_mlx_and_textures(t_game *gme);
// void init_variables_and_mlx_and_textures(t_game *game, const char *av[]);
t_game *init_variables_and_mlx_and_textures(t_game *game, const char *av[]);

#endif
