/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:09:11 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/15 13:56:15 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_comma(char *line);
int			check_color(char *line);
char		**split_color(char *line);
static char	*clean_spaces(const char *line);

// Check digit
int	check_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		// If the character is not a digit, comma, or space, return an error
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
			free_tab(rgb_parts);
			return (-1);
		}
		i++;
	}
	if (rgb_parts[i] != NULL && *rgb_parts[i] != '\0')
	{
		free_tab(rgb_parts);
		return (-1);
	}
	free_tab(rgb_parts);
	return (0);
}

// Split the color string into RGB parts
char	**split_color(char *line)
{
	char	*new_line;
	char	**rgb_parts;

	// Remove spaces from the line
	new_line = clean_spaces(line);
	if (!new_line)
		return (NULL);
	// Split the cleaned line by commas
	rgb_parts = ft_split(new_line, ',');
	free(new_line);
	return (rgb_parts);
}

// Clean space of the color
static char	*clean_spaces(const char *line)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	new_line = malloc(len + 1);
	if (!new_line)
		return (NULL);
	while (i < len && ft_isspace(line[i])) // Ignore first spaces
		i++;
	while (i < len)
	{
		// If is not a space, copy the charactere
		if (!ft_isspace(line[i]))
			new_line[j++] = line[i];
		i++;
	}
	// Remove ending spaces
	if (j > 0 && ft_isspace((new_line[j - 1])))
		j--;
	new_line[j] = '\0';
	return (new_line);
}
