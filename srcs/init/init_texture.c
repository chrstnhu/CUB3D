/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_texture.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/14 13:02:32 by leochen		   #+#	#+#			 */
/*   Updated: 2024/08/17 18:58:51 by chrhu			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_textures(t_data *data);
static int	*xpm_to_img(t_data *data, char *path);
static void	init_texture_img(t_data *data, t_img *image, char *path);
void		init_texture_pix(t_data *data);

// Initialize rays
void	init_ray(t_ray *ray)
{
	ray->camera_plane_x = 0;// 初始化摄像机平面的X坐标
	ray->ray_dir_x = 0;// 初始化射线在X方向上的方向向量
	ray->ray_dir_y = 0;// 初始化射线在Y方向上的方向向量
	ray->map_grid_x = 0;// 初始化射线所在地图网格的X坐标
	ray->map_grid_y = 0;// 初始化射线所在地图网格的Y坐标
	ray->step_x = 0;// 初始化射线在X方向上的步进
	ray->step_y = 0;// 初始化射线在Y方向上的步进
	ray->side_dist_x = 0;// 初始化射线到下一个X网格边界的距离
	ray->side_dist_y = 0;// 初始化射线到下一个Y网格边界的距离
	ray->delta_dist_x = 0;// 初始化射线每前进一个网格X距离的增量
	ray->delta_dist_y = 0;// 初始化射线每前进一个网格Y距离的增量
	ray->perp_wall_dist = 0;// 初始化射线到墙壁的垂直距离
	ray->hit_side = 0;// 初始化射线碰撞的墙壁面 (0: X方向的墙, 1: Y方向的墙)
	ray->wall_line_height = 0;// 初始化墙壁在屏幕上投影的高度
	ray->draw_start = 0;// 初始化墙壁在屏幕上绘制的起始点
	ray->draw_end = 0;// 初始化墙壁在屏幕上绘制的结束点
}

// Initialize texture img
void	init_textures(t_data *data)
{
	data->textures = ft_calloc(5, sizeof * data->textures);
	if (!data->textures)
		//clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	data->textures[NO] = xpm_to_img(data, data->texinfo.north);
	data->textures[SO] = xpm_to_img(data, data->texinfo.south);
	data->textures[EA] = xpm_to_img(data, data->texinfo.east);
	data->textures[WE] = xpm_to_img(data, data->texinfo.west);
}

// Transform xpm to img for minilibx
static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	y = 0;
	init_texture_img(data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * data->texinfo.size * data->texinfo.size);
	if (!buffer)
		//clean_exit
	y = 0;
	while (y < data->texinfo.size)
	{
		x = 0;
		while (x < data->texinfo.size)
		{
			buffer[y * data->texinfo.size + x]
				= tmp.addr[y * data->texinfo.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.mlx_img);
	return (buffer);
}

// Miss clean
static void	init_texture_img(t_data *data, t_img *image, char *path)
{
	init_img_clean(image);
	image->mlx_img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size,
			&data->texinfo.size);
	if (image->mlx_img == NULL)
		//clean_exit(data, err_msg("mlx", ERR_MLX_IMG, 1));
	image->addr = mlx_get_data_addr(image->mlx_img, &image->bpp,
				&image->line_len, &image->endian);
	return ;
}

// Miss clean
void	init_texture_pix(t_data *data)
{
	int	i;

	i = 0;
	if (data->texture_pixels != NULL)
		free_tab((void **)data->texture_pixels);
	data->texture_pixels = ft_calloc(data->win_height + 1, sizeof(int *));
	if (data->texture_pixels == NULL)
		//error_clean_exit("Error\nMalloc failed for texture pix\n", data);
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1, sizeof(int));
		if (data->texture_pixels[i] == NULL)
			//error_clean_exit("Error\nnMalloc failed for texture pix\n", data);
		i++;
	}
}
