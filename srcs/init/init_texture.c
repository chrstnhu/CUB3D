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

// Initialize rays -- OK
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
	printf(YELLOW"\nEnter init_textures\n"DEF);
	data->textures = ft_calloc(5, sizeof * data->textures);
	if (!data->textures)
		clean_exit(data, "malloc data texture failed", 1);
	data->textures[NO] = xpm_to_img(data, data->texinfo.north);
	printf("NO: %s\n", data->texinfo.north);
	data->textures[SO] = xpm_to_img(data, data->texinfo.south);
	printf("SO: %s\n", data->texinfo.south);
	data->textures[EA] = xpm_to_img(data, data->texinfo.east);
	printf("EA: %s\n", data->texinfo.east);
	data->textures[WE] = xpm_to_img(data, data->texinfo.west);
	printf("WE: %s\n", data->texinfo.west);
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
		clean_exit(data, "buffer xpm to img failed", 1);
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

static void	init_texture_img(t_data *data, t_img *image, char *path)
{
	static int i = 0;

	init_img_clean(image);
	i++;
	printf("Loading image from path: %s with index : %d\n", path, i );
	image->mlx_img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size,
			&data->texinfo.size);
	if (image->mlx_img == NULL)
	{
		printf("Error loading image from path: %s\n", path);
        clean_exit(data, "mlx_xmp_file_to_img error", 1);
	}
	image->addr = mlx_get_data_addr(image->mlx_img, &image->bpp,
				&image->line_len, &image->endian);
	if (image->addr == NULL)
        clean_exit(data, "mlx_get data_addr error", 1);
	return ;
}

//OK
void	init_texture_pix(t_data *data)
{
	int	i;

	i = 0;
	if (data->texture_pixels != NULL)
		free_tab((void **)data->texture_pixels);
	data->texture_pixels = ft_calloc(data->win_height + 1, sizeof(int *));
	if (data->texture_pixels == NULL)
		clean_exit(data, "Malloc failed for texture pix height", 1);
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1, sizeof(int));
		if (data->texture_pixels[i] == NULL)
			clean_exit(data, "Malloc failed for texture pix width", 1);
		i++;
	}
	printf(GREEN"Texture pixels allocated successfully\n"DEF);
}
