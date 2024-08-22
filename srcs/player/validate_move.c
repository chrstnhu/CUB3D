/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:08:14 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/22 13:10:55 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Check if the move is valid
int	validate_move(t_data *data, double x, double y)
{
	int	moved;

	moved = 0;
	if ((x > 0.25 && x <= data->wholemap.width - 1.25) && (y > 0.25
			&& y <= data->wholemap.height - 0.25))
	{
		data->player.pos_x = x;
		moved = 1;
	}
	if ((x > 0.25 && x <= data->wholemap.width - 1.25) && (y > 0.25
			&& y <= data->wholemap.height - 0.25))
	{
		data->player.pos_y = y;
		moved = 1;
	}
	return (moved);
}

int	rotate_player(t_data *data, double rotate_dir)
{
	double		rotate_speed;
	t_player	*p;
	double		tmp_x;

	rotate_speed = 0.015 * rotate_dir;
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
