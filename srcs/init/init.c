/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:18:43 by leochen           #+#    #+#             */
/*   Updated: 2024/08/19 11:31:44 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_img_clean(t_img *img);
static void	init_texinfo(t_texinfo *texinfo);
static void	init_wholemap(t_wholemap *wholemap);
static void	init_player(t_player *player);

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_height = 720;
	data->win_width = 960;
	data->player_count = 0;
	data->map = NULL;
	data->texture_pixels = NULL;
	data->textures = NULL;
	init_img_clean(&data->playermap);
	init_texinfo(&data->texinfo);
	init_wholemap(&data->wholemap);
	init_player(&data->player);
}

void	init_img_clean(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

static void	init_texinfo(t_texinfo *texinfo)
{
	texinfo->north = NULL;
	texinfo->south = NULL;
	texinfo->west = NULL;
	texinfo->east = NULL;
	texinfo->floor = malloc(3 * sizeof(int));
	if (!texinfo->floor)
		error_exit(RED"Error\nMemory allocation failed for floor color"DEF);
	texinfo->ceiling = malloc(3 * sizeof(int));
	if (!texinfo->ceiling)
	{
		free(texinfo->floor);
		error_exit(RED"Error\nMemory allocation failed for ceiling color"DEF);
	}
	texinfo->hex_floor = 0;
	texinfo->hex_ceiling = 0;
	texinfo->size = 0;
	texinfo->index = 0;
	texinfo->step = 0;
	texinfo->pos = 0;
	texinfo->x = 0;
	texinfo->y = 0;
}

static void	init_wholemap(t_wholemap *wholemap)
{
	wholemap->fd = 0;
	wholemap->line_count = 0;
	wholemap->path = NULL;
	wholemap->file = NULL;
	wholemap->height = 0;
	wholemap->width = 0;
	wholemap->index_end_of_map = 0;
}

static void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
}
