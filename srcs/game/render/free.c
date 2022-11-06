/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouib <adouib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:20:22 by adouib            #+#    #+#             */
/*   Updated: 2022/11/06 02:01:04 by adouib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/cub3d.h"

void	destroy_parser_allocations_more(t_game *game)
{
	if (game->parser->f->color)
		free(game->parser->f->color);
	if (game->parser->c->color)
		free(game->parser->c->color);
	if (game->parser->f)
		free(game->parser->f);
	if (game->parser->c)
		free(game->parser->c);
}

void	destroy_parser_allocations(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->parser->all_map)
		free(game->parser->all_map);
	if (game->parser->no->path)
		free(game->parser->no->path);
	if (game->parser->so->path)
		free(game->parser->so->path);
	if (game->parser->ea->path)
		free(game->parser->ea->path);
	if (game->parser->we->path)
		free(game->parser->we->path);
	if (game->parser->no)
		free(game->parser->no);
	if (game->parser->so)
		free(game->parser->so);
	if (game->parser->ea)
		free(game->parser->ea);
	if (game->parser->we)
		free(game->parser->we);
	if (game->cols)
		free(game->cols);
}

void	destroy_render_allocations(t_game *game)
{
	if (game->global_img->frame)
		mlx_destroy_image(game->mlx, game->global_img->frame);
	if (game->n_t_data->frame)
		mlx_destroy_image(game->mlx, game->n_t_data->frame);
	if (game->s_t_data->frame)
		mlx_destroy_image(game->mlx, game->s_t_data->frame);
	if (game->w_t_data->frame)
		mlx_destroy_image(game->mlx, game->w_t_data->frame);
	if (game->e_t_data->frame)
		mlx_destroy_image(game->mlx, game->e_t_data->frame);
	if (game->global_img)
		free(game->global_img);
	if (game->n_t_data)
		free(game->n_t_data);
	if (game->s_t_data)
		free(game->s_t_data);
	if (game->w_t_data)
		free(game->w_t_data);
	if (game->e_t_data)
		free(game->e_t_data);
	if (game->parser)
		free(game->parser);
	if (game)
		free(game);
}

void	free_all(t_game *game)
{
	destroy_parser_allocations(game);
	destroy_parser_allocations_more(game);
	destroy_render_allocations(game);
}
