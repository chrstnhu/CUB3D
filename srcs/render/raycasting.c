/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   raycasting.c										:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/08/14 13:02:32 by leochen			#+#	#+#				*/
/*   Updated: 2024/08/17 19:43:50 by chrhu			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		calc_delta_dist(t_data *data, int x);
void		calc_side_dist(t_data *data);
void		dda(t_data *data, t_ray *ray);

// Raycasting
int	raycasting(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->win_width)
	{
		calc_delta_dist(data, x);
		calc_side_dist(data);
		dda(data, &data->ray);
		calculate_line_height(data, &data->ray);
		update_texture_pix(data, &data->texinfo, &data->ray, x);
		x++;
	}
	return (0);
}

// Calculate the delta distance
void	calc_delta_dist(t_data *data, int x)
{
	init_ray(&data->ray);
	data->ray.camera_plane_x = 2 * x / (double)data->win_width - 1;
	data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x
		* data->ray.camera_plane_x;
	data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y
		* data->ray.camera_plane_x;
	data->ray.map_grid_x = (int)data->player.pos_x;
	data->ray.map_grid_y = (int)data->player.pos_y;
	if (data->ray.ray_dir_x == 0)
		data->ray.delta_dist_x = 1e30;
	else
		data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	if (data->ray.ray_dir_y == 0)
		data->ray.delta_dist_y = 1e30;
	else
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

// Calculate the side distance
static void	calc_side_dist_x(t_ray *ray, double pos_x)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->map_grid_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_grid_x + 1.0 - pos_x) * ray->delta_dist_x;
	}
}

static void	calc_side_dist_y(t_ray *ray, double pos_y)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->map_grid_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_grid_y + 1.0 - pos_y) * ray->delta_dist_y;
	}
}

void	calc_side_dist(t_data *data)
{
	t_ray		*ray;
	t_player	*player;

	ray = &data->ray;
	player = &data->player;
	calc_side_dist_x(ray, player->pos_x);
	calc_side_dist_y(ray, player->pos_y);
}
