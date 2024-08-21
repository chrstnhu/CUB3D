/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:08:14 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/21 15:39:48 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int validate_move(t_data *data, double x, double y)
// {
// 	int moved;

// 	moved = 0;
// 	if ((x > 0.25 && x <= data->wholemap.width - 1.25)
// 		&& (y > 0.25 && y <= data->wholemap.height - 0.25))
// 	{
// 		data->player.pos_x = x;
// 		moved = 1;
// 	}
// 	if ((x > 0.25 && x <= data->wholemap.width - 1.25)
// 		&& (y > 0.25 && y <= data->wholemap.height - 0.25))
// 	{
// 		data->player.pos_y = y;
// 		moved = 1;
// 	}
// 	return (moved);
// }


static bool	is_valid_pos_in_map(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= data->wholemap.width - 1.25)
		return (false);
	if (y < 0.25 || y >= data->wholemap.height -0.25)
		return (false);
	return (true);
}

static bool	is_valid_pos(t_data *data, double x, double y)
{
	if (is_valid_pos_in_map(data, x, y))
		return (true);
	return (false);
}

int	validate_move(t_data *data, double x, double y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(data, x, data->player.pos_y))
	{
		data->player.pos_x = x;
		moved = 1;
	}
	if (is_valid_pos(data, data->player.pos_x, y))
	{
		data->player.pos_y = y;
		moved = 1;
	}
	return (moved);
}
