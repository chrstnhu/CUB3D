/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/21 18:50:17 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_data *data);
int 	render(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_exit(RED"Usage:./cub3D maps/file.cub"DEF);
	
	if (file_valid(av[1]) == -1)
		error_exit(RED"File open failed or not end with .cub"DEF);
	// printf("1. here before check_cub_file()\n");
	check_cub_file(av[1]);
	init_data(&data);
	//printf(YELLOW"Before parse_cub_file\n"DEF);
	parse_cub_file(&data, av[1]);

	//printf(YELLOW"Before check_map\n"DEF);
	check_map(&data);
	// if (check_map(data) == -1)
		// free_data(data);
	//printf(YELLOW"Before init_mlx\n"DEF);
	init_mlx(&data);
	
	//printf(YELLOW"Before init_textures\n"DEF);
	init_textures(&data);

	//printf(YELLOW"Before render_screen\n"DEF);
	render_screen(&data);
	//printf(YELLOW"After render_screen\n"DEF);
	
	// file -> input_handler
	mlx_hook(data.win, ClientMessage, NoEventMask, close_win, &data); // close with the X
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}

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

int	render(t_data *data)
{
	data->player.has_moved += player_move(data);
	if (data->player.has_moved == 0)
		return (0);
	render_screen(data);
	return (0);
}