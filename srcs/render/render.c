/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:02:32 by leochen           #+#    #+#             */
/*   Updated: 2024/08/17 19:47:36 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		render_frame(t_data *data);
void		init_img(t_data *data, t_img *image, int width, int height);
static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y);
static void	set_image_pixel(t_img *image, int x, int y, int color);

void	render_screen(t_data *data)
{
	init_texture_pix(data);
	init_ray(&data->ray);
	raycasting(data);
	render_frame(data);
}

void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.mlx_img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, image.mlx_img);
}

void	init_img(t_data *data, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->mlx_img = mlx_new_image(data->mlx, width, height);
	if (image->mlx_img == NULL)
		//clean_exit(data, err_msg("mlx", ERR_MLX_IMG, 1));
	image->addr = mlx_get_data_addr(image->mlx_img, &image->bpp,
				&image->line_len, &image->endian);
	return ;
}

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

static void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_len / 4) + x;
	image->addr[pixel] = color;
}
