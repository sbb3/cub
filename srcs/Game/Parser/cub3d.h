/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:43:18 by labenall          #+#    #+#             */
/*   Updated: 2022/10/23 10:47:29 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_type
{
	char	*path;
}			t_type;

typedef struct s_color
{
	char	*color;
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_map
{
	char	*all_map;
	char	**map;
	t_type	*no;
	t_type	*so;
	t_type	*we;
	t_type	*ea;
	t_color	*f;
	t_color	*c;
	char	p_direction;
	int		xp;
	int		yp;
	int		height;
	int		width;
}		t_map;

void	exit_erreur(char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *s);
int		is_sapce(char c);
int		ft_atoi(char *s);
char	*get_contet(char *map, size_t *i);
t_color	*get_content_color(char *map, size_t *i);
char	**get_content_of_map(char *map, size_t *i);
char	*get_map(size_t size, int fd);
char	*get_line(char *map, size_t *i);
int		get_nbr_char(char *map, int i);
size_t	get_nbr_line(char *map, size_t i);
size_t	get_size_map(char *name_map);
char	*get_number(char *map, size_t *i, size_t a);
int		cheak_name(char *name);
int		cheak_name_texure(char *name);
void	cheak_type(t_map *map_struct);
void	cheak_content_map(t_map *map_struct);
void	cheak_map(t_map *map);
char	*encodec_color(int r, int g, int b);
int		ft_isdigit(char c);
int		is_player(char c);
int		is_char_map(char c);
t_map	*initial_map_struct(size_t size, int fd);
void	initial_h_w(t_map *map_struct);
char	*ft_copier(char *s, size_t size);
void	ignore_first(char *map, size_t *i);
void	cas_stel2(t_map *map, char *type, int *nbr_type, size_t *i);
void	cas_strlen1(t_map *map, char *type, int *nbr_type, size_t *i);
size_t	cas_is_space_or_new_line(char *map, size_t i, size_t r, int k);
void	cheak_texure(t_map *map_struct);

#endif
