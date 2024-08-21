/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   raycasting.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/14 13:02:32 by leochen		   #+#	#+#			 */
/*   Updated: 2024/08/17 19:43:50 by chrhu			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/cub3d.h"

//void	calc_delta_dist(t_data *data);
void 	calc_delta_dist(t_data *data, int x);
void	calc_side_dist(t_data *data);
void	dda(t_data *data, t_ray *ray);

int raycasting(t_data *data)
{
    int x;
	// printf("Raycasting: player at (%f, %f), direction: (%f, %f)\n",
        //    data->player.pos_x, data->player.pos_y, 
        //    data->player.dir_x, data->player.dir_y);
    x = 0;
    while (x < data->win_width)
    {
        calc_delta_dist(data, x);
        calc_side_dist(data);
        dda(data, &data->ray);  // Pass data->ray instead of &ray
        calculate_line_height(data, &data->ray);
        update_texture_pix(data, &data->texinfo, &data->ray, x);
        x++;
    }
    return (0);
}

void calc_delta_dist(t_data *data, int x)
{
    init_ray(&data->ray);
    // data->ray.camera_plane_x = 2 * ((double)data->ray.map_grid_x / data->win_width) - 1;
	//modif 
	data->ray.camera_plane_x = 2 * x / (double)data->win_width - 1;
    data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x * data->ray.camera_plane_x;
    data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y * data->ray.camera_plane_x;
    
    // printf("Ray direction: (%f, %f)\n", data->ray.ray_dir_x, data->ray.ray_dir_y);
    
    data->ray.map_grid_x = (int)data->player.pos_x;
    data->ray.map_grid_y = (int)data->player.pos_y;
    
    // printf("Initial map position: (%d, %d)\n", data->ray.map_grid_x, data->ray.map_grid_y);
    
    if (data->ray.ray_dir_x == 0)
        data->ray.delta_dist_x = 1e30;
    else
        data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
    if (data->ray.ray_dir_y == 0)
        data->ray.delta_dist_y = 1e30;
    else
        data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);

// printf("Ray direction: (%f, %f)\n", data->ray.ray_dir_x, data->ray.ray_dir_y);
    // printf("Delta distances: (%f, %f)\n", data->ray.delta_dist_x, data->ray.delta_dist_y);
}


void	calc_side_dist(t_data *data) // more than 25 line
{
	t_ray		*ray;
	t_player	*player;
	double		pos_x; // 将玩家的位置存储在局部变量中
	double		pos_y;

	ray = &data->ray;
	player = &data->player;
	pos_x = player->pos_x;
	pos_y = player->pos_y;
	// 设置射线在x方向上的步进方向和初始边距距离
	if (ray->ray_dir_x < 0) // dir_x < 0 表示射线向左 | 玩家朝向西方
	{
		ray->step_x = -1; //step_x是射线在x方向上的步进方向 单位是格子 为-1表示向左
		ray->side_dist_x = (pos_x - ray->map_grid_x) * ray->delta_dist_x;
	}
	else //玩家朝向东方
	{
		ray->step_x = 1; // 光线向右移动
		ray->side_dist_x = (ray->map_grid_x + 1.0 - pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0) // 设置射线在y方向上的步进方向和初始边距距离
	{ // 玩家朝向北方
		ray->step_y = -1; // 光线向上移动 
		ray->side_dist_y = (pos_y - ray->map_grid_y) * ray->delta_dist_y;
	}
	else // 玩家朝向南方 
	{
		ray->step_y = 1; // 光线向下移动
		ray->side_dist_y = (ray->map_grid_y + 1.0 - pos_y) * ray->delta_dist_y;
	}
	// printf("Side distances: (%f, %f)\n", ray->side_dist_x, ray->side_dist_y);
}

void dda(t_data *data, t_ray *ray)
{
    int hit;

    hit = 0;
    // printf("Starting DDA: player at (%f, %f), ray direction (%f, %f)\n", 
        //    data->player.pos_x, data->player.pos_y, ray->ray_dir_x, ray->ray_dir_y);
    // printf("Initial map position: (%d, %d)\n", ray->map_grid_x, ray->map_grid_y);
    
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

        // printf("Checking position (%d, %d)\n", ray->map_grid_x, ray->map_grid_y);

        if (ray->map_grid_y < 0 || ray->map_grid_x < 0 ||
            ray->map_grid_y >= data->wholemap.height ||
            ray->map_grid_x >= data->wholemap.width)
        {
            //printf("Ray out of bounds\n");
            break;
        }
        else if (data->map[ray->map_grid_y][ray->map_grid_x] == '1')
        {
            hit = 1;
            // printf("Wall hit at (%d, %d)\n", ray->map_grid_x, ray->map_grid_y);
        }
    }
	// printf("Updated side_dist_x: %f, side_dist_y: %f\n", ray->side_dist_x, ray->side_dist_y);

}
