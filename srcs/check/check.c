/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/14 11:32:18 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	file_valid(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(&file[len - 4], ".cub", 4))
		return (-1);
	return (0);
}

int	path_valid(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (ft_strncmp(&path[len - 5], ".xpm", 4))
		return (-1);
	// if (access(path, F_OK) < 0)
	// 	return (-1);
	return (0);
}

int	check_texture(char *line)
{
	printf("Enter check_texture\n");
	jump_space(line);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		printf("Line : %s\n", line);
		line += 2;// Move the pointer past the identifier ("NO", "SO", etc.)
		jump_space(line);// Jump over any spaces after the identifier
		if (path_valid(line) == -1)
			return (-1);
		return (0);// Successfully processed a texture line, return success
	}
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		printf("Line : %s\n", line);
		line += 2;
		jump_space(line);// Move the pointer past the identifier ("F", "C")
		if ((check_digit(line) == -1))
			return (-1);
		if ((check_color(line) == -1))
			return (-1);
		return (0);// Successfully processed a color line, return success
	}
	return (0);/* -1 change to 0*/
}
