/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:02:32 by leochen           #+#    #+#             */
/*   Updated: 2024/08/21 13:04:04 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x);
static void	get_texture_index(t_data *data, t_ray *ray);

// Calcule the wall heigth
void	calculate_line_height(t_data *data, t_ray *ray)
{
	// 根据射线击中的墙的方向计算到墙的距离
	if (ray->hit_side == 0) // 如果射线击中的是垂直边界
		ray->perp_wall_dist = (ray->map_grid_x - data->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else // 如果射线击中的是水平边界
		ray->perp_wall_dist = (ray->map_grid_y - data->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
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
	//addd
	ray->wall_x -= floor(ray->wall_x);
}

// Update texture original
void	update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_texture_index(data, ray);
	if (data->textures[tex->index] == NULL)
        return; // Early exit to avoid segmentation fault
	tex->x = (int)(ray->wall_x * tex->size);	
	if ((ray->hit_side == 0 && ray->ray_dir_x < 0)
		|| (ray->hit_side == 1 && ray->ray_dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->wall_line_height;	
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->wall_line_height / 2) * tex->step;	
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


// Update texture with printf
/*
void	update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	printf(YELLOW"Enter texture pix\n"DEF);
	int			y;
	int			color;

	get_texture_index(data, ray);
	printf(YELLOW"After texture pix\n"DEF);
	printf("Texture Index: %d\n", tex->index);
    printf("Texture Size: %d\n", tex->size);
    printf("Texture X: %d, Texture Y: %d\n", tex->x, tex->y);

	// Vérifier si la texture est bien chargée
	if (data->textures[tex->index] == NULL) {
        printf(RED"Error: Texture pointer is NULL for index %d\n"DEF, tex->index);
        return; // Early exit to avoid segmentation fault
    }

	// Calcul de la coordonnée X dans la texture
	tex->x = (int)(ray->wall_x * tex->size);
	printf("Wall X: %f, Tex X: %d\n", ray->wall_x, tex->x);

	// Vérification des coordonnées X et Y
	if (tex->x < 0 || tex->x >= tex->size) {
        printf(RED"Error: Tex X out of bounds! Tex X: %d, Tex Size: %d\n"DEF, tex->x, tex->size);
        return;
    }

	if (tex->y < 0 || tex->y >= tex->size) {
 	   printf(RED"Error: Tex Y out of bounds! Tex Y: %d, Tex Size: %d\n"DEF, tex->y, tex->size);
    return;

	}
	if ((ray->hit_side == 0 && ray->ray_dir_x < 0)
		|| (ray->hit_side == 1 && ray->ray_dir_y > 0))
		tex->x = tex->size - tex->x - 1;

	// Calcul de l'incrément pour la position dans la texture
	tex->step = 1.0 * tex->size / ray->wall_line_height;
	printf("Wall Line Height: %d, Tex Step: %f\n", ray->wall_line_height, tex->step);
	
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->wall_line_height / 2) * tex->step;
	printf("Draw Start: %d, Draw End: %d, Tex Pos: %f\n", ray->draw_start, ray->draw_end, tex->pos);
	
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;

		// Vérifier si la coordonnée Y est valide
		if (tex->y < 0 || tex->y >= tex->size) {
	        printf(RED"Error: Tex Y out of bounds! Tex Y: %d, Tex Size: %d\n"DEF, tex->y, tex->size);
	        return;
	    }

		// Extraction de la couleur de la texture
		color = data->textures[tex->index][tex->size * tex->y + tex->x];

		// Vérification des couleurs nulles
		// if (color == 0)
	        // printf(RED"Warning: Color at (Tex X: %d, Tex Y: %d) is zero, possible issue.\n"DEF, tex->x, tex->y);

		// Ajustement de la couleur pour certaines textures
		if (tex->index == NO || tex->index == EA)
			color = (color >> 1) & 8355711;

		// Assignation de la couleur au pixel de l'écran
		if (color > 0)
        	data->texture_pixels[y][x] = color;
		// else
    		// printf(YELLOW"Pixel at screen (%d, %d) not set because color is %d.\n"DEF, y, x, color);
		
		y++;
	}
}
*/

// Get the texture
static void	get_texture_index(t_data *data, t_ray *ray)
{
	// printf(YELLOW"Enter get_texture_index\n"DEF);
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
