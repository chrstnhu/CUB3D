/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:02:32 by leochen           #+#    #+#             */
/*   Updated: 2024/09/21 19:34:08 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_wall_height(t_data *data, t_ray *ray);
void		update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x);
static void	set_texture_params(t_data *data, t_texinfo *tex, t_ray *ray);
static void	get_texture_index(t_data *data, t_ray *ray);

// Calculate the height of the wall to be drawn
void	calculate_line_height(t_data *data, t_ray *ray, t_player *player)
{
	int	hit_side;

	hit_side = ray->hit_side;
	if (hit_side == HIT_SIDE_X)
	{
		ray->perp_wall_dist = (ray->map_grid_x - player->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else if (hit_side == HIT_SIDE_Y)
	{
		ray->perp_wall_dist = (ray->map_grid_y - player->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
	update_wall_height(data, ray);
	if (hit_side == HIT_SIDE_X)
	{
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else if (hit_side == HIT_SIDE_Y)
	{
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
}

// Update wall height
static void	update_wall_height(t_data *data, t_ray *ray)
{
	double	win_height;
	double	wall_line_height;

	win_height = data->win_height;
	ray->wall_line_height = (int)(win_height / ray->perp_wall_dist);
	wall_line_height = ray->wall_line_height;
	ray->draw_start = -(wall_line_height) / 2 + win_height / 2;
	if (ray->draw_start < 0)
	{
		ray->draw_start = 0;
	}
	ray->draw_end = wall_line_height / 2 + win_height / 2;
	if (ray->draw_end >= win_height)
	{
		ray->draw_end = win_height - 1;
	}
}

// Update texture pixels for rendering the wall
void	update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int	y;
	int	color;

	y = ray->draw_start;
	get_texture_index(data, ray);
	set_texture_params(data, tex, ray);
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NO || tex->index == EA)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}

// Configure texture parameters
static void	set_texture_params(t_data *data, t_texinfo *tex, t_ray *ray)
{
	if (data->textures[tex->index] == NULL)
		return ;
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->hit_side == HIT_SIDE_X && ray->ray_dir_x < 0)
		|| (ray->hit_side == HIT_SIDE_Y && ray->ray_dir_y > 0))
	{
		tex->x = tex->size - tex->x - 1;
	}
	tex->step = 1.0 * tex->size / ray->wall_line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->wall_line_height / 2) * tex->step;
}

// Get the texture based on the direction of the wall hit
static void	get_texture_index(t_data *data, t_ray *ray)
{
	if (ray->hit_side == HIT_SIDE_X)
	{
		if (ray->ray_dir_x < 0)
			data->texinfo.index = WE;
		else
			data->texinfo.index = EA;
	}
	else if (ray->hit_side == HIT_SIDE_Y)
	{
		if (ray->ray_dir_y < 0)
			data->texinfo.index = NO;
		else
			data->texinfo.index = SO;
	}
}
