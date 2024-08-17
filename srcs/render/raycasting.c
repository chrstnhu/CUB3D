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

void	calc_delta_dist(t_data *data);
void	calc_side_dist(t_data *data);
void	dda(t_data *data, t_ray *ray);

int	raycasting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x < data->win_width)
	{
		calc_delta_dist(data);
		calc_side_dist(data);
		dda(data, &ray);
		calculate_line_height(data, &ray);
		update_texture_pix(data, &data->texinfo, &ray, x);
		x++;
	}
	return (0);
}

void	calc_delta_dist(t_data *data)
{
	init_ray(&data->ray);
	//将屏幕的 x 坐标转换为 -1 到 1 之间的值
	data->ray.camera_plane_x = 2 * (data->ray.map_grid_x 
			/ (double)data->win_width) - 1;
	//计算射线的方向
	data->ray.ray_dir_x = data->player.dir_x 
		+ data->player.plane_x * data->ray.camera_plane_x;
	data->ray.ray_dir_y = data->player.dir_y
		+ data->player.plane_y * data->ray.camera_plane_x;
	// 初始化射线的地图坐标为玩家的当前所在网格
	data->ray.map_grid_x = (int)data->player.pos_x;
	data->ray.map_grid_y = (int)data->player.pos_y;
	// 计算射线在 X 和 Y 方向上穿越一个完整的地图方块所需的距离
	// 避免除以 0 的情况发生
	if (data->ray.ray_dir_x == 0)
		data->ray.delta_dist_x = 1;
	else
		data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	if (data->ray.ray_dir_y == 0)
		data->ray.delta_dist_y = 1;
	else
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
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
}

void	dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	// DDA算法, 直到射线碰到墙壁为止
	while (hit == 0)
	{
		// 比较距离以确定射线首先跨越的是
		if (ray->side_dist_x < ray->side_dist_y) // 射线首先跨越的是X方向的垂直边界
		{
			ray->side_dist_x += ray->delta_dist_x; // 增加到达下一个垂直边界的距离
			ray->map_grid_x += ray->step_x;//在X方向上前进一格
			ray->hit_side = 0;// 表示碰撞发生在垂直墙壁（X方向）
		}
		else // 射线首先跨越的是Y方向的水平边界
		{
			ray->side_dist_y += ray->delta_dist_y; // 增加到达下一个水平边界的距离
			ray->map_grid_y += ray->step_y; // 在Y方向上前进一格
			ray->hit_side = 1; // 表示碰撞发生在水平墙壁（Y方向）
		}
		// 检查射线是否超出地图的边界
		if (ray->map_grid_y < 0.25
			|| ray->map_grid_x < 0.25
			|| ray->map_grid_y > data->wholemap.height - 0.25
			|| ray->map_grid_x > data->wholemap.width - 1.25)
			break ;
		// 检查射线是否碰到墙壁（地图中为'1'的部分）
		else if (data->map[ray->map_grid_y][ray->map_grid_x] == '1')
			hit = 1;
	}
}
