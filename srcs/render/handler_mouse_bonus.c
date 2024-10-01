/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_mouse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:27:29 by chrhu             #+#    #+#             */
/*   Updated: 2024/10/01 14:39:47 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Adjust the mouse position if it's out of window
static int	adjust_mouse_pos(t_data *data, int x, int y)
{
	if (x > data->win_width)
	{
		x = 0;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
	else if (x < 0)
	{
		x = data->win_width;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
	return (x);
}

// Rotate the point of view with mouse
int	mouse_motion(int new_x, int y, t_data *data)
{
	static int	prev_x = WIN_WIDTH / 2;
	const float	sensitivity = 0.1;
	int			delta_x;

	new_x = adjust_mouse_pos(data, new_x, y);
	if (new_x == prev_x)
		return (0);
	delta_x = new_x - prev_x;
	if (delta_x != 0)
		data->player.has_moved += rotate_player(data, delta_x * sensitivity);
	prev_x = new_x;
	return (0);
}
