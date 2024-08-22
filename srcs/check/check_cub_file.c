/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/22 16:15:38 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Check the file name and open
int	file_valid(char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file);
	if (ft_strncmp(&file[len - 4], ".cub", 4))
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("Error : open file", 2);
		ft_putendl_fd(DEF, 2);
		return (-1);
	}
	return (0);
}

// Check in file
int	process_line(char *line, t_map_elements *elements)
{
	if (line[0] == '\n')
	{
		free(line);
		return (0);
	}
	if (check_texture(line, elements) == -1)
	{
		free(line);
		get_next_line(-42);
		return (error_exit("Invalid texture or color"));
	}
	free(line);
	return (0);
}

int	check_cub_file(char *path)
{
	int				fd;
	char			*line;
	t_map_elements	elements;

	init_map_element(&elements);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error : open file", 2), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(line, &elements))
		{
			close(fd);
			return (1);
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (validate_map(&elements) == -1)
		return (error_exit("Missing required map elements"));
	return (0);
}

// Check texture
int	check_texture_path(char **line, int *element_flag)
{
	*element_flag = 1;
	*line += 2;
	jump_space(line);
	if (path_valid(*line) == -1)
		return (-1);
	return (0);
}

int	check_texture(char *line, t_map_elements *elements)
{
	trim(&line);
	if (!ft_strncmp(line, "NO ", 3))
		return (check_texture_path(&line, &elements->north));
	else if (!ft_strncmp(line, "SO ", 3))
		return (check_texture_path(&line, &elements->south));
	else if (!ft_strncmp(line, "WE ", 3))
		return (check_texture_path(&line, &elements->west));
	else if (!ft_strncmp(line, "EA ", 3))
		return (check_texture_path(&line, &elements->east));
	else if (!ft_strncmp(line, "F ", 2))
		return (check_color_element(&line, &elements->floor));
	else if (!ft_strncmp(line, "C ", 2))
		return (check_color_element(&line, &elements->ceiling));
	return (0);
}
