/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:11:43 by leochen           #+#    #+#             */
/*   Updated: 2024/08/22 14:13:37 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Check if it has one element
int	validate_map(t_map_elements *elements)
{
	if (!elements->north || !elements->south || !elements->west
		|| !elements->east || !elements->floor || !elements->ceiling)
		return (-1);
	return (0);
}

// Check the path of .xpm
int	path_valid(char *path)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (ft_strnstr(path, ".xpm", len) == NULL)
	{
		ft_putendl_fd("Texture path didn t end with .xpm", 2);
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Failed open file", 2);
		return (-1);
	}
	close(fd);
	return (0);
}

int	check_color_element(char **line, int *element_flag)
{
	*element_flag = 1;
	*line += 2;
	jump_space(line);
	if (check_digit(*line) == -1 || check_color(*line) == -1)
		return (-1);
	return (0);
}
