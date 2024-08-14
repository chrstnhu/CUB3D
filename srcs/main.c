/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/14 19:58:45 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_cub_file(char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_exit(RED"Error\nInvalid file"DEF));
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
			free(line);
		else
		{
			if (check_texture(line) == -1)
				return (error_exit(RED"Error\nInvalid texture"DEF));
			free(line);
		}
		line = get_next_line(fd);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_exit(RED"Usage:./cub3D maps/file.cub"DEF);
	if (file_valid(av[1]) == -1)
		error_exit(RED"Invalid file, please end with .cub"DEF);
	check_cub_file(av[1]);
	init_data(&data);
	//ADD
	parse_cub_file(&data, av[1]);
	check_map(&data);
	// if (check_map(data) == -1)
		// free_data(data);
	return (0);
}
