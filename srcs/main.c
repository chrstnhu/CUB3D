/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/14 11:30:00 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_map(t_data *data, char *path)
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
			if (parse_line(data, line) == -1)
				return (error_exit(RED"Error\nInvalid parsing"DEF));
			free(line);
		}
		line = get_next_line(fd);
	}
	return (0);
}

int	check_map(char *path)
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
	check_map(av[1]);
	init_data(&data);
	//ADD
	parse_map(&data, av[1]);
	return (0);
}
