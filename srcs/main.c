/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/22 13:47:12 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_map_is_at_the_end(t_wholemap *map);
void		init_mlx(t_data *data);
int			render(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_exit("Usage:./cub3D maps/file.cub");
	if (file_valid(av[1]) == -1)
		error_exit("Open failed or not end with .cub");
	check_cub_file(av[1]);
	init_data(&data);
	if (parse_cub_file(&data, av[1]) == -1)
		clean_exit(&data, "Error parsing cub file", 1);
	if (check_map_is_at_the_end(&data.wholemap) == -1)
		clean_exit(&data, "Map is not at the end of the file", 1);
	check_map(&data);
	init_mlx(&data);
	init_textures(&data);
	render_screen(&data);
	mlx_hook(data.win, ClientMessage, NoEventMask, close_win, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}

static int	check_map_is_at_the_end(t_wholemap *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

// Initialize mlx window
void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_exit(data, "mlx_init failed", 1);
	data->win = mlx_new_window(data->mlx, 960, 720, "Cub3D");
	if (!data->win)
		clean_exit(data, "mlx_new_window failed", 1);
	return ;
}

// Render
int	render(t_data *data)
{
	data->player.has_moved += player_move(data);
	if (data->player.has_moved == 0)
		return (0);
	render_screen(data);
	return (0);
}
