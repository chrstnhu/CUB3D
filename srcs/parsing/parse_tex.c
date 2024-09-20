/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:42:29 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/20 12:56:00 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			parse_texture(t_texinfo *texinfo, char *line);
static int	handle_texture(char **texture, char *line);
int			parse_color(t_texinfo *texinfo, int *color, char *line);

// Parse line
int	parse_line(t_data *data, char *line)
{
	if (line[0] == '\0' || line[0] == '\n')
		return (0);
	trim(&line);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(&data->texinfo, line));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(&data->texinfo, data->texinfo.floor, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(&data->texinfo, data->texinfo.ceiling, line));
	return (0);
}

// Parse the texture
int	parse_texture(t_texinfo *texinfo, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (handle_texture(&texinfo->north, line));
	else if (!ft_strncmp(line, "SO ", 3))
		return (handle_texture(&texinfo->south, line));
	else if (!ft_strncmp(line, "WE ", 3))
		return (handle_texture(&texinfo->west, line));
	else if (!ft_strncmp(line, "EA ", 3))
		return (handle_texture(&texinfo->east, line));
	else
		return (-1);
}

// Handle the texture
static int	handle_texture(char **texture, char *line)
{
	if (*texture)
		return (-1);
	line += 2;
	jump_space(&line);
	*texture = ft_strdup(line);
	return (0);
}

// Parse color (floor, ceiling)
int	parse_color(t_texinfo *texinfo, int *color, char *line)
{
	char	**rgb_parts;

	if ((color == texinfo->floor && texinfo->hex_floor != 0)
		|| (color == texinfo->ceiling && texinfo->hex_ceiling != 0))
		return (-1);
	if (!color)
		return (-1);
	rgb_parts = split_color(line + 2);
	if (!rgb_parts)
		return (-1);
	color[0] = ft_atoi(rgb_parts[0]);
	color[1] = ft_atoi(rgb_parts[1]);
	color[2] = ft_atoi(rgb_parts[2]);
	free_tab((void **)rgb_parts);
	if (color == texinfo->floor)
		texinfo->hex_floor = (color[0] << 16) | (color[1] << 8) | color[2];
	else if (color == texinfo->ceiling)
		texinfo->hex_ceiling = (color[0] << 16) | (color[1] << 8) | color[2];
	return (0);
}
