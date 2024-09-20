/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:37:43 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/20 12:57:35 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_longest_line(t_wholemap *map, int i);
int			count_map_lines(t_data *data, char **map, int x);

// Fill map tab
int	fill_map_tab(t_wholemap *wholemap, char **map_tab, int start)
{
	int	i;
	int	j;

	i = 0;
	wholemap->width = get_longest_line(wholemap, start) - 1;
	while (i < wholemap->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (wholemap->width + 1));
		if (!map_tab[i])
			return (error_msg("Map_tab malloc failed", -1));
		while (wholemap->file[start][j] && wholemap->file[start][j] != '\n')
		{
			map_tab[i][j] = wholemap->file[start][j];
			j++;
		}
		while (j < wholemap->width)
			map_tab[i][j++] = ' ';
		map_tab[i][j++] = '\0';
		i++;
		start++;
	}
	map_tab[i] = NULL;
	return (0);
}

// Find and return the longest line (row)
static int	get_longest_line(t_wholemap *map, int i)
{
	int	longest_line;
	int	current_line;

	current_line = ft_strlen(map->file[i]);
	longest_line = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		current_line = ft_strlen(map->file[i]);
		if (current_line > longest_line)
			longest_line = ft_strlen(map->file[i]);
		i++;
	}
	return (longest_line);
}

// Count line of the map
int	count_map_lines(t_data *data, char **map, int x)
{
	int	count;
	int	y;

	count = 0;
	while (map[x])
	{
		y = 0;
		while (ft_isspace(map[x][y]))
			y++;
		if (map[x][y] != '1')
			break ;
		x++;
		count++;
	}
	data->wholemap.index_end_of_map = x;
	return (count);
}
