/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:26 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/20 16:47:14 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_walls(char **map, int x, int y, int rows);
static int	is_adjacent_to_space(char **map, int x, int y, int rows);
static int	is_surrounded_by_valid_walls(char **map, int x, int y, int rows);

// Check border walls
int	check_border_walls(t_data *data, char **map)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->wholemap.height)
	{
		y = 0;
		while (y < data->wholemap.width)
		{
			if (map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'E' || map[x][y] == 'W')
			{
				if (x == 0 || x == data->wholemap.height - 1 || y == 0
					|| y == data->wholemap.width - 1)
					return (-1);
				if (check_walls(map, x, y, data->wholemap.height) == -1)
					return (-1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

// Check normal wall and irregular wall
static int	check_walls(char **map, int x, int y, int total_rows)
{
	int	row_len;

	row_len = ft_strlen(map[x]);
	if (x < 0 || x >= total_rows || y < 0 || y >= row_len)
		return (-1);
	if (ft_strchr("0NSEW", map[x][y]))
	{
		if (is_adjacent_to_space(map, x, y, total_rows))
			return (-1);
		if (is_surrounded_by_valid_walls(map, x, y, total_rows))
			return (0);
		return (-1);
	}
	return (0);
}

// Check if the cell is adjacent to a empty space (irregular wall)
static int	is_adjacent_to_space(char **map, int x, int y, int rows)
{
	int	len;
	int	top;
	int	down;
	int	left;
	int	right;

	len = ft_strlen(map[x]);
	top = x - 1;
	down = x + 1;
	left = y - 1;
	right = y + 1;
	if ((top >= 0 && ft_isspace(map[top][y])) || (down < rows
			&& ft_isspace(map[down][y])) || (left >= 0
			&& ft_isspace(map[x][left])) || (right < len
			&& ft_isspace(map[x][right])))
		return (1);
	if ((top >= 0 && left >= 0 && ft_isspace(map[top][left])) || (top >= 0
			&& right < len && ft_isspace(map[top][right])) || (down < rows
			&& left >= 0 && ft_isspace(map[down][left])) || (down < rows
			&& right < len && ft_isspace(map[down][right])))
		return (1);
	return (0);
}

// Check if the cell is surrounded by a wall (irregular wall)
static int	is_surrounded_by_valid_walls(char **map, int x, int y, int rows)
{
	int	len;
	int	top;
	int	down;
	int	left;
	int	right;

	len = ft_strlen(map[x]);
	top = x - 1;
	down = x + 1;
	left = y - 1;
	right = y + 1;
	if ((top < 0 || ft_strchr("10NSEW", map[top][y])) || (down >= rows
			|| ft_strchr("10NSEW", map[down][y])) || (left < 0
			|| ft_strchr("10NSEW", map[x][left])) || (right >= len
			|| ft_strchr("10NSEW", map[x][right])))
		return (1);
	if ((top >= 0 && left >= 0 && ft_strchr("10NSEW", map[top][left]))
		|| (top >= 0 && right < len && ft_strchr("10NSEW", map[top][right]))
		|| (down < rows && left >= 0 && ft_strchr("10NSEW", map[down][left]))
		|| (down < rows && right < len && ft_strchr("10NSEW",
				map[down][right])))
		return (1);
	return (0);
}
