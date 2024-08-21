/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:07:15 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/21 16:10:29 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int move_player_forward(t_data *data);
static int move_player_backward(t_data *data);
static int move_player_left(t_data *data);
static int move_player_right(t_data *data);
static int rotate_player(t_data *data, double rotate_dir);

int	player_move(t_data *data)
{
	int moved;

	moved = 0;
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

static int move_player_forward(t_data *data)
{
	double x;
	double y;

	x = data->player.pos_x + data->player.dir_x * 0.0100;
	y = data->player.pos_y + data->player.dir_y * 0.0100;
	//printf("Move forward (x: %f, y: %f)\n", x, y);
	return (validate_move(data, x, y));
}

static int move_player_backward(t_data *data)
{
	double x;
	double y;

	x = data->player.pos_x - data->player.dir_x * 0.0100;
	y = data->player.pos_y - data->player.dir_y * 0.0100;
	//printf("Move backward (x: %f, y: %f)\n", x, y);
	return (validate_move(data, x, y));
}

static int move_player_left(t_data *data)
{
	double x;
	double y;

	x = data->player.pos_x + data->player.dir_y * 0.0100;
	y = data->player.pos_y - data->player.dir_x * 0.0100;
	//printf("Move left (x: %f, y: %f)\n", x, y);
	return (validate_move(data, x, y));
}

static int move_player_right(t_data *data)
{
	double x;
	double y;

	x = data->player.pos_x - data->player.dir_y * 0.0100;
	y = data->player.pos_y + data->player.dir_x * 0.0100;
	//printf("Move right (x: %f, y: %f)\n", x, y);
	return (validate_move(data, x, y));
}

static int rotate_player(t_data *data, double rotate_dir)
{
	
	double rotate_speed;
	t_player *p;
	double tmp_x;
	
	rotate_speed = 0.015 * rotate_dir;
	p = &data->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotate_speed) - p->dir_y * sin(rotate_speed);
	p->dir_y = tmp_x * sin(rotate_speed) + p->dir_y * cos(rotate_speed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotate_speed) - p->plane_y * sin(rotate_speed);
	p->plane_y = tmp_x * sin(rotate_speed) + p->plane_y * cos(rotate_speed);	
	return (1);
}