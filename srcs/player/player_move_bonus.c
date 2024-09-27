/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:07:15 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/27 13:22:43 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	move_player_forward(t_data *data);
static int	move_player_backward(t_data *data);
static int	move_player_left(t_data *data);
static int	move_player_right(t_data *data);

// Player move
int	player_move(t_data *data)
{
	int	moved;
	int	collision;

	moved = 0;
	collision = 0;
	if (data->player.move_y == 1)
		moved += move_player_forward(data);
	if (data->player.move_y == -1)
		moved += move_player_backward(data);
	if (data->player.move_x == -1)
		moved += move_player_left(data);
	if (data->player.move_x == 1)
		moved += move_player_right(data);
	if (data->player.rotate != 0)
		moved += rotate_player(data, data->player.rotate);
	return (moved);
}

// Move forward ↑
static int	move_player_forward(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x + data->player.dir_x * SPEED;
	y = data->player.pos_y + data->player.dir_y * SPEED;
	return (validate_move_bonus(data, x, y));
}

// Move backward ↓ 
static int	move_player_backward(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x - data->player.dir_x * SPEED;
	y = data->player.pos_y - data->player.dir_y * SPEED;
	return (validate_move_bonus(data, x, y));
}

// Move left ←
static int	move_player_left(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x + data->player.dir_y * SPEED;
	y = data->player.pos_y - data->player.dir_x * SPEED;
	return (validate_move_bonus(data, x, y));
}

// Move right →
static int	move_player_right(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x - data->player.dir_y * SPEED;
	y = data->player.pos_y + data->player.dir_x * SPEED;
	return (validate_move_bonus(data, x, y));
}
