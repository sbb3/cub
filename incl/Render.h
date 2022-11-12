/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/11/12 10:53:56 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <mlx.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

/* Keys codes */
# define ESC_KEY 53
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124

/* Measurement Variables */

# define SPEED 15 /* move step */
# define ROTATION_SPEED 7
# define FOV 60 // field of view of the player

/* Window Measurement */

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 768
# define SQUARE_SIZE 64
# define SQUARE_WIDTH 64
# define SQUARE_HEIGHT 64

typedef struct s_n_texture
{
	void			*frame;
	char			*frame_addr;
	int				bpp;
	int				line_bytes;
	int				endn;
	unsigned int	texture_color;
	int				w;
	int				h;
}	t_n_texture;

typedef struct s_s_texture
{
	void			*frame;
	char			*frame_addr;
	int				bpp;
	int				line_bytes;
	int				endn;
	unsigned int	texture_color;
	int				w;
	int				h;
}	t_s_texture;

typedef struct s_w_texture
{
	void			*frame;
	char			*frame_addr;
	int				bpp;
	int				line_bytes;
	int				endn;
	unsigned int	texture_color;
	int				w;
	int				h;
}	t_w_texture;

typedef struct s_e_texture
{
	void			*frame;
	char			*frame_addr;
	int				bpp;
	int				line_bytes;
	int				endn;
	unsigned int	texture_color;
	int				w;
	int				h;
}	t_e_texture;

typedef struct s_global_image
{
	void			*frame;
	char			*frame_addr;
	int				bpp;
	int				line_bytes;
	int				endn;
}	t_global_image;

typedef struct s_game
{
	t_global_image	*global_img;
	t_n_texture		*n_t_data;
	t_s_texture		*s_t_data;
	t_w_texture		*w_t_data;
	t_e_texture		*e_t_data;
	t_map			*parser;
	void			*mlx;
	void			*win;
	char			**map;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	int				map_width;
	int				map_height;
	int				window_width;
	int				window_height;
	int				rays;
	float			ppos_x;
	float			ppos_y;
	float			pdir_x;
	float			pdir_y;
	float			player_angle;
	float			ray_angle;
	float			ray_angle_increment;
	int				ray_up;
	int				ray_down;
	int				ray_left;
	int				ray_right;
	int				half_fov;
	int				is_north;
	int				is_south;
	int				is_west;
	int				is_east;
	int				wall_hit;
	float			wall_hit_x;
	float			wall_hit_y;
	float			h_wall_hit_x;
	float			h_wall_hit_y;
	float			v_wall_hit_x;
	float			v_wall_hit_y;
	float			wall_height;
	float			dist_to_projection_plane;
	float			distorted_ray_distance_to_wall;
	float			ray_distance;
	float			h_dist_to_wall;
	float			v_dist_to_wall;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	int				h_hit;
	int				texture_offset_x;
	int				texture_offset_y;
	float			xinter;
	float			yinter;
	float			xstep;
	float			ystep;
	int				rays_count;
	int				*cols;
}	t_game;

/* Init */
t_game			*init_variables_and_mlx_and_textures(t_game *game, \
	const char *av[]);
void			init_variables(t_game *game, const char *av[]);
void			init_player_starting_direction(t_game *game);

/* Draw utils */
void			re_draw(t_game *game);
void			paint(t_game *game, int x);
void			paint_ceiling(t_game *game, int x);
void			draw_floor(t_game *game, int x);
void			paint_walls(t_game *game, int startX);

/*Images*/
t_global_image	*create_global_image(t_game *game);
t_n_texture		*create_north_texture_image(t_game *game);
t_s_texture		*create_south_texture_image(t_game *game);
t_w_texture		*create_west_texture_image(t_game *game);
t_e_texture		*create_east_texture_image(t_game *game);
unsigned int	get_the_color_from_north_texture(t_game *game);
unsigned int	get_the_color_from_south_texture(t_game *game);
unsigned int	get_the_color_from_west_texture(t_game *game);
unsigned int	get_the_color_from_east_texture(t_game *game);
void			set_the_texture_color_on_walls(t_game *game, int x, int y, \
	unsigned int color);
void			coloring_pixel(t_game *game, int x, int y, unsigned int color);

/* Movements */
int				movements(int keycode, t_game *game);
void			move_up(t_game *game);
void			move_down(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
int				is_wall_on_left(t_game *game, int angle);
int				is_wall_on_right(t_game *game, int angle);
int				is_wall_on_down(t_game *game);
int				is_wall_on_up(t_game *game);

/* Raycaster */
void			raycasting_then_drawing(t_game *game);
void			vertical_intersection_and_steps(t_game *game);
void			horizontal_intersection_and_steps(t_game *game);
void			vertical_wall_coordinates(t_game *game);
void			horizontal_wall_coordinates(t_game *game);
void			calculations(t_game *game);
void			get_the_short_distance(t_game *game);
void			get_projected_wall_height(t_game *game);
void			horizontal_wall_collision(t_game *game);
void			vertical_wall_collision(t_game *game);
float			distance(float startX, float startY, float endX, float endY);
int				out_of_container_width_and_height(t_game *game, \
	int coordinate_x, int coordinate_y);
void			reset_vars_to_zero(t_game *game);

/* other utils */
float			deg_2_rad(float angleInDegree);
void			ray_direction(t_game *game);
void			correct_angle(float *angle);
float			fix_angle(float angle);
void			quit(t_game *game, char *s);
void			free_all(t_game *game);
void			destroy_parser_allocations(t_game *game);
void			destroy_parser_allocations_more(t_game *game);
void			destroy_render_allocations(t_game *game);
int				red_cross_quit(t_game *game);
char			**free_map(char **token);
void			*ft_calloc(size_t count, size_t size);
void			exit_if_null(void *p, char *message);
unsigned int	rgb_encoding(int red, int green, int blue);
int				calc_each_row_columns_then_get_the_max_col(t_game *game);
int				map_width(char *s);
int				map_height(char *s[]);

#endif
