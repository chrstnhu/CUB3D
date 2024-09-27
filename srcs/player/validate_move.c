/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:08:14 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/27 14:11:11 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Check if the move is in the map
int	validate_move(t_data *data, double x, double y)
{
	int	moved;

	moved = 0;
	if ((x > 1 && x <= data->wholemap.width - 1)
		&& (y > 1 && y <= data->wholemap.height - 1))
	{
		data->player.pos_x = x;
		moved = 1;
	}
	if ((x > 1 && x <= data->wholemap.width - 1)
		&& (y > 1 && y <= data->wholemap.height - 1))
	{
		data->player.pos_y = y;
		moved = 1;
	}
	return (moved);
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
