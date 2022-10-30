/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:07:43 by adouib            #+#    #+#             */
/*   Updated: 2022/10/30 15:19:37 by adouib           ###   ########.fr       */
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

/* textures path */
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

# define SPEED 15
# define ROTATION 6
# define FOV 60 // field of view of the player

/* Window Measurement */

# define SQUARE_SIZE 64
# define SQUARE_WIDTH 64
# define SQUARE_HEIGHT 64

/* Minimap Measurement */
# define MINIMAP_SIZE 10

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
	int				map_width;
	int				map_height;
	int				window_width;
	int				window_height;
	int				half_win_height;
	int				rays;
	int				pos_x; // rename to like : player_pos_x
	int				pos_y;
	float			pdir_x;		// 1
	float			pdir_y;		// 0
	float			player_angle; // player angle
	float			ray_angle;
	float			ray_angle_increment;
	int				ray_up;
	int				ray_down;
	int				ray_left;
	int				ray_right;
	int				half_fov;		// half of view of the player
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
	float			wall_height;	// projected_wall_height
	float			dist_to_wall; // distance_to_projected_wall
	float			distorted_ray_distance_to_wall;
	float			ray_distance; // correct_ray_distance
	float			h_dist_to_wall; // horizontal_distance_to_wall
	float			v_dist_to_wall; // vertical_distance_to_wall
	int				wall_top_pixel;	   // projected wall top pixel
	int				wall_bottom_pixel; // projected wall bottom pixel
	int				h_hit;
	int				texture_offset_x;
	int				texture_offset_y;
	float			xinter;
	float			yinter;
	float			xstep;
	float			ystep;
	int				rays_count;
	int				minimap_width;
	int				minimap_height;
}	t_game;

/* Init */
t_game			*init_variables_and_mlx_and_textures(t_game *game, \
	const char *av[]);
void			init_variables(t_game *game, const char *av[]);
void			init_player_starting_direction(t_game *game);
void			re_draw(t_game *game);

/* Draw utils */
void			draw(t_game *game);
void			redraw(t_game *game);
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
void			coloring_pixel(t_game *game, int x, int y, int color);

/* Movements */
int				movements(int keycode, t_game *game);
void			move_up(t_game *game);
void			move_down(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

/* Raycaster */
void			raycaster(t_game *game);
void			intersections_and_steps_vertically(t_game *game);
void			intersections_and_steps_horizontally(t_game *game);
void			looking_for_wall_coordinates_vertically(t_game *game);
void			looking_for_wall_coordinates_horizontally(t_game *game);
void			calculations(t_game *game);
void			get_the_short_distance(t_game *game);
void			get_projected_wall_height(t_game *game);
void			ray_wall_collision_horizontally(t_game *game);
void			ray_wall_collision_vertically(t_game *game);
float			distance(int startX, int startY, int endX, int endY);
int				out_of_container_width_and_height(t_game *game);
void			reset_vars_to_zero(t_game *game);

/* other utils */
float			degree_to_radian(float angleInDegree);
void			ray_direction(t_game *game);
void			correct_angle(float *angle);
void			quit(t_game *game, char *s);
void			free_all(t_game *game);
void			destroy_parser_allocations(t_game *game);
void			destroy_parser_allocations_more(t_game *game);
void			destroy_render_allocations(t_game *game);
int				red_cross_quit(t_game *game);
char			**free_map(char **token);
void			*ft_calloc(size_t count, size_t size);
void			exit_if_null(void *p, char *message);

/* Minimap */
void			minimap(t_game *game);
void			draw_minimap_walls(t_game *game);
void			draw_minimap_arrow(t_game *game);
void			draw_arrow_line(t_game *game, int start_x, int start_y, \
	float new_angle);
int				scale_down(int minimap_size, int window_size, \
	int coordinate);
void			edit_pixel(t_game *game, int startX, int startY, int color);

#endif
