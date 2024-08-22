/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:09:11 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/22 11:31:57 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_comma(char *line);
int			check_color(char *line);
char		**split_color(char *line);

// Check digit
int	check_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isdigit(line[i]) || line[i] == ',' || ft_isspace(line[i])))
			return (-1);
		else if (check_comma(line) == -1)
			return (-1);
		i++;
	}
	return (0);
}

// Check comma : (',,') or (',' != 2)
static int	check_comma(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			return (-1);
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (-1);
	return (0);
}

// Check if the color is like rgb
int	check_color(char *line)
{
	char	**rgb_parts;
	int		i;

	i = 0;
	rgb_parts = split_color(line);
	if (!rgb_parts)
		return (-1);
	while (i < 3)
	{
		if (!rgb_parts[i] || (ft_atoi(rgb_parts[i]) < 0
				|| ft_atoi(rgb_parts[i]) > 255))
		{
			free_tab((void **)rgb_parts);
			return (-1);
		}
		i++;
	}
	if (rgb_parts[i] != NULL && *rgb_parts[i] != '\0')
	{
		free_tab((void **)rgb_parts);
		return (-1);
	}
	free_tab((void **)rgb_parts);
	return (0);
}

// Split the color string into RGB parts
char	**split_color(char *line)
{
	char	*new_line;
	char	**rgb_parts;

	new_line = clean_spaces(line);
	if (!new_line)
		return (NULL);
	rgb_parts = ft_split(new_line, ',');
	free(new_line);
	return (rgb_parts);
}
