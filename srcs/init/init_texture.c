/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   init_texture.c										:+:	  :+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/08/14 13:02:32 by leochen			#+#	#+#			 */
/*   Updated: 2024/08/17 18:58:51 by chrhu			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		init_textures(t_data *data);
static int	*xpm_to_img(t_data *data, char *path);
static void	init_texture_img(t_data *data, t_img *image, char *path);
void		init_texture_pix(t_data *data);

// Initialize rays
void	init_ray(t_ray *ray)
{
	ray->camera_plane_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_grid_x = 0;
	ray->map_grid_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->hit_side = 0;
	ray->wall_line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

// Initialize texture img
void	init_textures(t_data *data)
{
	data->textures = ft_calloc(5, sizeof * data->textures);
	if (!data->textures)
		clean_exit(data, "malloc data texture failed", 1);
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
	buffer = ft_calloc(1, sizeof * buffer * data->texinfo.size
			* data->texinfo.size);
	if (!buffer)
		clean_exit(data, "buffer xpm to img failed", 1);
	y = 0;
	while (y < data->texinfo.size)
	{
		x = 0;
		while (x < data->texinfo.size)
		{
			buffer[y * data->texinfo.size + x] = tmp.addr[y * data->texinfo.size
				+ x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.mlx_img);
	return (buffer);
}

// Initialize texture image
static void	init_texture_img(t_data *data, t_img *image, char *path)
{
	static int	i = 0;

	init_img_clean(image);
	i++;
	image->mlx_img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size,
			&data->texinfo.size);
	if (image->mlx_img == NULL)
		clean_exit(data, "mlx_xmp_file_to_img error", 1);
	image->addr = (int *)mlx_get_data_addr(image->mlx_img, &image->bpp,
			&image->line_len, &image->endian);
	if (image->addr == NULL)
		clean_exit(data, "mlx_get data_addr error", 1);
	return ;
}

// Initialize texture pixel
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
}
