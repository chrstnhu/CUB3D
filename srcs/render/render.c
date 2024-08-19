/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   render.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/14 13:02:32 by leochen		   #+#	#+#			 */
/*   Updated: 2024/08/19 14:22:54 by chrhu			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		render_frame(t_data *data);
void		init_img(t_data *data, t_img *image, int width, int height);
static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y);
static void	set_image_pixel(t_img *image, int x, int y, int color);

void	render_screen(t_data *data)
{
	printf(YELLOW"\nBefore init_texture_pix\n"DEF);
	init_texture_pix(data);

	printf(YELLOW"\nBefore init_ray\n"DEF);
	init_ray(&data->ray);

	printf(YELLOW"\nBefore raycasting\n"DEF);
	raycasting(data);

	printf(YELLOW"\nBefore render_frame\n"DEF);
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
	// Debbug -> is null
	if (data->win != NULL && image.mlx_img != NULL)
		mlx_put_image_to_window(data->mlx, data->win, image.mlx_img, 0, 0);
	else
		clean_exit(data, "Window or image is NULL", 1);
	// End debbug
	mlx_destroy_image(data->mlx, image.mlx_img);
}

void	init_img(t_data *data, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->mlx_img = mlx_new_image(data->mlx, width, height);
	if (image->mlx_img == NULL)
		clean_exit(data, "mlx_new_image failed", 1);
	image->addr = mlx_get_data_addr(image->mlx_img, &image->bpp,
				&image->line_len, &image->endian);
	if (image->addr == NULL)
		clean_exit(data, "mlx_get_data_addr failed", 1);
	return ;
}

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	//Debug
	if (x >= data->win_width || y >= data->win_height || x < 0 || y < 0)
	{
		printf(RED"Error: Coordinates (%d, %d) are out of bounds\n"DEF, x, y);
		return;
	}
	if (data->texture_pixels == NULL || data->texture_pixels[y] == NULL) {
		printf(RED"Error: texture_pixels not initialized or row %d is NULL\n"DEF, y);
		exit(1);
	}
	//End debug
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

// Windows : top white and bottom black
static void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_len / 4) + x;
	image->addr[pixel] = color;
}

// Window : top color ceiling, bottom color floor
/* 
static void set_image_pixel(t_img *image, int x, int y, int color)
{
	if (image->addr == NULL) 
	{
		printf(RED"Error: image->addr is NULL\n"DEF);
		exit(1);
	}

	// Convertir line_len en nombre de pixels
	size_t width = image->line_len / sizeof(int); 
	size_t height = image->line_len / (size_t)sizeof(int);
		
	// Convertir les coordonnées x et y en size_t pour les comparaisons
	size_t x_size_t = (size_t)x;
	size_t y_size_t = (size_t)y;

	// Vérifier les limites
	if (x_size_t >= width || y_size_t >= height)
	{
		printf(RED"Error: Pixel coordinates (%d, %d) are out of bounds\n"DEF, x, y);
		exit(1);
	}

	// Calculer l'index du pixel
	size_t pixel_index = y_size_t * width + x_size_t;

	// Vérifier que l'index du pixel est valide
	if (pixel_index >= width * height) {
		printf(RED"Error: Pixel index %zu is out of bounds\n"DEF, pixel_index);
		exit(1);
	}

	// Assigner la couleur au pixel
	((int *)image->addr)[pixel_index] = color;
}
*/