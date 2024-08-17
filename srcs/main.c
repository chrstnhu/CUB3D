/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/17 19:47:18 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_exit(RED"Usage:./cub3D maps/file.cub"DEF);
	if (file_valid(av[1]) == -1)
		error_exit(RED"Invalid file, please end with .cub"DEF);
	check_cub_file(av[1]);
	init_data(&data);
	parse_cub_file(&data, av[1]);
	check_map(&data);
	// if (check_map(data) == -1)
		// free_data(data);
	init_mlx(&data);
	//init_textures(&data);
	//render_screen(&data);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		//clean exit
	data->win = mlx_new_window(data->mlx, 960, 720, "Cub3D");
	if (!data->win)
		//clean exit
	return ;
}
