/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:43:47 by labenall          #+#    #+#             */
/*   Updated: 2022/11/02 21:41:21 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

// function kanpranti biha map man ba3d ma7waltha l array dyal string
/*void	print_array_string(char **array_str)
{
	int	i;

	i = 0;
	while (array_str[i])
	{
		printf("%s\n", array_str[i]);
		i++;
	}
}*/

// function kanchiki fiha samya wach katsali b .cub
/*void	print_strct_map(t_map *map)
{
	if (map)
	{
		printf("NO	\n");
		if (map->no)
		{
			printf("%s\n", map->no->path);
		}
		printf("SO	\n");
		if (map->so)
		{
			if (map->so->path != NULL)
				printf("%s\n", map->so->path);
		}
		printf("WE	\n");
		if (map->we)
			printf("%s\n", map->we->path);
		printf("EA	\n");
		if (map->ea)
			printf("%s\n", map->ea->path);
		printf("F	\n");
		if (map->f)
		{
			printf("%d,", (map->f->r));
			printf("%d,", (map->f->g));
			printf("%d\n", (map->f->b));
			printf("encoded :%s\n", map->f->color);
		}
		printf("C	\n");
		if (map->c)
		{
			printf("%d,", (map->c->r));
			printf("%d,", (map->c->g));
			printf("%d\n", (map->c->b));
			printf("encoded :%s\n", map->c->color);
		}
		if (map->map)
		{
			print_array_string(map->map);
		}
		else
			printf("NULL\n");
	}
	else
		printf("map est NULL");
}*/

// function kaninitailzi fiha struct dyal map 
t_map	*initial_map_struct(size_t size, int fd)
{
	t_map	*map_struct;

	map_struct = malloc(sizeof(t_map));
	map_struct->all_map = NULL;
	map_struct->all_map = get_map(size, fd);
	if (map_struct->all_map == NULL)
		exit_erreur("Map is NULL");
	map_struct->map = NULL;
	map_struct->no = NULL;
	map_struct->so = NULL;
	map_struct->we = NULL;
	map_struct->ea = NULL;
	map_struct->f = NULL;
	map_struct->c = NULL;
	map_struct->p_direction = 0;
	map_struct->xp = 0;
	map_struct->yp = 0;
	return (map_struct);
}

//hna kanparsi okantchiki wach kayan chi erreur 
t_map	*parser(const char *av[])
{
	t_map	*map_struct;
	int		fd;

	if (cheak_name(av[1]))
		exit_erreur("Name of file must end with .cub");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit_erreur("Check Existence or  Access Control of file");
	map_struct = initial_map_struct(get_size_map(av[1]), fd);
	cheak_map(map_struct);
	cheak_type(map_struct);
	cheak_content_map(map_struct);
	return (map_struct);
}
