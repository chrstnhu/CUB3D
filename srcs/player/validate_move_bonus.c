/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_move_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:08:14 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/27 13:24:54 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	display_collision(t_data *data);
int			rotate_player(t_data *data, double rotate_dir);

// Check if the move is valid and avoid wall collision
int	validate_move_bonus(t_data *data, double new_x, double new_y)
{
	int		moved;
	char	cell_x;
	char	cell_y;

	moved = 0;
	cell_x = data->map[(int)data->player.pos_y][(int)new_x];
	if (ft_strchr("0NSWE", cell_x))
	{
		data->player.pos_x = new_x;
		moved = 1;
	}
	else if (cell_x == '1')
		display_collision(data);
	cell_y = data->map[(int)new_y][(int)data->player.pos_x];
	if (ft_strchr("0NSWE", cell_y))
	{
		data->player.pos_y = new_y;
		moved = 1;
	}
	else if (cell_y == '1')
		display_collision(data);
	return (moved);
}

// Display a message warning collision
static void	display_collision(t_data *data)
{
	void	*large_image;
	char	*msg;
	int		width;
	int		height;

	msg = "Warning, you hit a wall";
	large_image = mlx_xpm_file_to_image(data->mlx,
			"textures/warning.xpm", &width, &height);
	if (large_image)
	{
		mlx_string_put(data->mlx, data->win, 10, 15, 0xFF0000, msg);
		mlx_put_image_to_window(data->mlx, data->win,
			large_image, 10, 20);
		mlx_destroy_image(data->mlx, large_image);
	}
	else
		mlx_string_put(data->mlx, data->win, 20, 20, 0xFF0000, msg);
}

// Rotate the point of view of the player
int	rotate_player(t_data *data, double rotate_dir)
{
	double		rotate_speed;
	t_player	*p;
	double		tmp_x;

	rotate_speed = SPEED * rotate_dir;
	p = &data->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotate_speed) - p->dir_y * sin(rotate_speed);
	p->dir_y = tmp_x * sin(rotate_speed) + p->dir_y * cos(rotate_speed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotate_speed) - p->plane_y
		* sin(rotate_speed);
	p->plane_y = tmp_x * sin(rotate_speed) + p->plane_y * cos(rotate_speed);
	return (1);
}
