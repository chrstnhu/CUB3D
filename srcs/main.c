/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/15 16:00:31 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	file_valid(char *file);

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
	return (0);
}

static int	file_valid(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(&file[len - 4], ".cub", 4))
		return (-1);
	return (0);
}
