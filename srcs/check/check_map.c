/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:26 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/14 19:58:31 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Missing check surrounded wall

static int add_player_pos(t_data *data, char **map)
{
	int x;
	int y;

	if (data->player.dir == '\0')
		return (-1);
	x = 0;
	y = 0;
	while (map[x])
	{
		y = 0;
		while(map[x][y])
		{
			if (ft_strchr("NSEW", map[x][y]))
			{
				// Place the player at the center of the bloc;
				data->player.pos_x = (double)x + 0.5;
				data->player.pos_y = (double)y + 0.5;
			}
			y++;
		}
		x++;
	}
	return (0);
}

static int check_map_char(t_data *data, char **map)
{
	int i;
	int j;
	int player_count;

	i = -1;
	player_count = 0;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j])
		{
			while(ft_isspace(map[i][j]))
				j++;
			if (!ft_strchr("10NSEW", map[i][j]) || player_count > 1)
				return (error_msg("Invalid char", -1));
			if (ft_strchr("NSEW", map[i][j]))
			{
				player_count++;
				data->player.dir = map[i][j];
			}
		}
	}
	if (player_count == 0 )
		return (error_msg("No player", -1));
	return (0);
}

int check_map(t_data *data)
{
	if (!data->map)
		return (error_msg("Invalid : no map", -1));
	
	//check map wall

	if (data->wholemap.height < 3 || data->wholemap.width < 3)
		return (error_msg("Invalid : map too small", -1));
	if (check_map_char(data, data->map) == -1)
		return (error_msg("Invalid character", -1));
	if (add_player_pos(data, data->map) == -1)
		return (error_msg("Invalid player direction", -1));
	return (0);
}