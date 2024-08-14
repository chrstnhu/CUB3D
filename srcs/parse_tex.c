/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:42:29 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/14 11:26:14 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_texture(t_texinfo *texinfo, char *line)
{
	printf("----Enter parse texture ----\n");
	if (!ft_strncmp(line, "NO ", 3))
	{
		texinfo->north = ft_strdup(line + 3);
		printf("Dup : %s\n", texinfo->north);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		texinfo->south = ft_strdup(line + 3);
		printf("Dup : %s\n", texinfo->south);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		texinfo->west = ft_strdup(line + 3);
		printf("Dup : %s\n", texinfo->west);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		texinfo->east = ft_strdup(line + 3);
		printf("Dup : %s\n", texinfo->east);
	}
	else
		return (-1);
	return (0);
}

int	parse_color(t_texinfo *texinfo, int *color, char *line)
{
	char	**rgb_parts;

	printf("Line : %s\n", line);
	if (!color)
		return (-1);
	rgb_parts = split_color(line + 2);
	if (!rgb_parts)
		return (-1);
	color[0] = ft_atoi(rgb_parts[0]);
	color[1] = ft_atoi(rgb_parts[1]);
	color[2] = ft_atoi(rgb_parts[2]);
	free_tab(rgb_parts, 0);
	if (color == texinfo->floor)
	{
		texinfo->hex_floor = (color[0] << 16) | (color[1] << 8) | color[2];
		printf("Floor Color (Decimal): %ld\n", texinfo->hex_floor);
	}
	else if (color == texinfo->ceiling)
	{
		texinfo->hex_ceiling = (color[0] << 16) | (color[1] << 8) | color[2];
		printf("Ceiling Color (Decimal): %ld\n", texinfo->hex_ceiling);
	}
	return (0);
}

int	parse_line(t_data *data, char *line)
{
	// Skip empty lines
	if (line[0] == '\0' || line[0] == '\n')
		return (0);
	// Check if the line contains texture information
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(&data->texinfo, line));
	// Check if the line contains color information
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(&data->texinfo, data->texinfo.floor, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(&data->texinfo, data->texinfo.ceiling, line));
	// If it's not a texture or color, it must be part of the map
	// (Handling of map parsing will come later)
	return (0);
}
