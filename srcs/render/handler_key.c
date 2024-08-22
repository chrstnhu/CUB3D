/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:27:29 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/22 13:12:17 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Close window and clean
int	close_win(t_data *data)
{
	clean_exit(data, "Window closed", 0);
	return (0);
}

// Handler key press
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

// Handler key release
int	key_release(int keysym, t_data *data)
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
