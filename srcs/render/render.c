/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   render.c											:+:	  :+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/08/14 13:02:32 by leochen			#+#	#+#			 */
/*   Updated: 2024/08/19 14:22:54 by chrhu			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		render_frame(t_data *data);
void		init_img(t_data *data, t_img *image, int width, int height);
static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y);
static void	set_image_pixel(t_img *image, int x, int y, int color);

// Render screen visual
void	render_screen(t_data *data)
{
	init_texture_pix(data);
	init_ray(&data->ray);
	raycasting(data);
	render_frame(data);
}

// Render frame
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
	if (data->win != NULL && image.mlx_img != NULL)
		mlx_put_image_to_window(data->mlx, data->win, image.mlx_img, 0, 0);
	else
		clean_exit(data, "Window or image is NULL", 1);
	mlx_destroy_image(data->mlx, image.mlx_img);
}

// Initialize image
void	init_img(t_data *data, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->mlx_img = mlx_new_image(data->mlx, width, height);
	if (image->mlx_img == NULL)
		clean_exit(data, "mlx_new_image failed", 1);
	image->addr = (int *)mlx_get_data_addr(image->mlx_img, &image->bpp,
			&image->line_len, &image->endian);
	if (image->addr == NULL)
		clean_exit(data, "mlx_get_data_addr failed", 1);
	return ;
}

// Set frame image pixel on the window
static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	int	color;

	color = data->texture_pixels[y][x];
	if (x >= data->win_width || y >= data->win_height || x < 0 || y < 0)
		return ;
	if (data->texture_pixels == NULL || data->texture_pixels[y] == NULL)
		return ;
	if (color > 0)
		set_image_pixel(image, x, y, color);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

// Set image to pixel
static void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_len / 4) + x;
	image->addr[pixel] = color;
}
