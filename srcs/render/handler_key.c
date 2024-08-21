/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:27:29 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/21 16:04:02 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_win(t_data *data)
{
	clean_exit(data, "Window closed", 0);
	return (0);
}

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_win(data);
	if (keysym == XK_w || keysym == XK_W)
		data->player.move_y = 1;
	if (keysym == XK_s || keysym == XK_S)
		data->player.move_y = -1;
	if (keysym == XK_a || keysym == XK_A)
		data->player.move_x = -1;
	if (keysym == XK_d || keysym == XK_D)
		data->player.move_x = 1;
	if (keysym == XK_Left)
		data->player.rotate -= 1;
	if (keysym == XK_Right)
		data->player.rotate += 1;
	return (0);
}

int key_release(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_win(data);
	if ((keysym == XK_w || keysym == XK_W) && data->player.move_y == 1)
		data->player.move_y = 0;
	if ((keysym == XK_s || keysym == XK_S) && data->player.move_y == -1)
		data->player.move_y = 0;
	if ((keysym == XK_a || keysym == XK_A) && data->player.move_x == -1)
		data->player.move_x = 0;
	if ((keysym == XK_d || keysym == XK_D) && data->player.move_x == 1)
		data->player.move_x = 0;
	if (keysym == XK_Left && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (keysym == XK_Right && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);	
}