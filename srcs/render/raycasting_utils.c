/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:02:32 by leochen           #+#    #+#             */
/*   Updated: 2024/09/20 13:03:10 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x);
static void	get_texture_index(t_data *data, t_ray *ray);
void		dda(t_data *data, t_ray *ray);

// Calcule the wall heigth
void	calculate_line_height(t_data *data, t_ray *ray)
{
	if (ray->hit_side == 0)
		ray->perp_wall_dist = (ray->map_grid_x - data->player.pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_grid_y - data->player.pos_y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
	ray->wall_line_height = (int)(data->win_height / ray->perp_wall_dist);
	ray->draw_start = -(ray->wall_line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->hit_side == 0)
		ray->wall_x = data->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = data->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

// Update texture original
void	update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(data, ray);
	if (data->textures[tex->index] == NULL)
		return ;
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->hit_side == 0 && ray->ray_dir_x < 0) || (ray->hit_side == 1
			&& ray->ray_dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->wall_line_height;
	tex->pos = (ray->draw_start - data->win_height / 2 + ray->wall_line_height
			/ 2) * tex->step;
	y = ray->draw_start;
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

// Get the texture
static void	get_texture_index(t_data *data, t_ray *ray)
{
	if (ray->hit_side == 0)
	{
		if (ray->ray_dir_x < 0)
			data->texinfo.index = WE;
		else
			data->texinfo.index = EA;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			data->texinfo.index = SO;
		else
			data->texinfo.index = NO;
	}
}

// Use dda algorithm
void	dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_grid_x += ray->step_x;
			ray->hit_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_grid_y += ray->step_y;
			ray->hit_side = 1;
		}
		if (ray->map_grid_y < 0 || ray->map_grid_x < 0
			|| ray->map_grid_y >= data->wholemap.height
			|| ray->map_grid_x >= data->wholemap.width)
			break ;
		else if (data->map[ray->map_grid_y][ray->map_grid_x] == '1')
			hit = 1;
	}
}
