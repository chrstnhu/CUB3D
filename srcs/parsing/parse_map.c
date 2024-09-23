/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   parse_map.c										:+:		:+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/08/13 10:30:50 by chrhu				#+#	#+#			 */
/*   Updated: 2024/08/15 11:36:27 by chrhu			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_map(t_data *data, char **map, int x, int y);
static int	create_map(t_data *data, char **map, int x);
static void	replace_space(t_data *data);

// Parse the map
int	parse_map(t_data *data, char **map)
{
	int	x;
	int	y;
	int	ret;

	ret = 0;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			ret = get_map(data, map, x, y);
			if (ret == -1)
				return (-1);
			else
				return (0);
			y++;
		}
		x++;
	}
	return (0);
}

// Extract and get map
static int	get_map(t_data *data, char **map, int x, int y)
{
	while (map[x] != NULL)
	{
		while (map[x][y] == ' ' || map[x][y] == '\t' || map[x][y] == '\n')
			y++;
		if (ft_isdigit((unsigned char)map[x][y]))
		{
			y = 0;
			if (create_map(data, map, x) == -1)
				return (error_msg(data->wholemap.path, -1));
			else
				break ;
		}
		x++;
		y = 0;
	}
	return (0);
}

// Create and fill the map
static int	create_map(t_data *data, char **map, int x)
{
	data->wholemap.height = count_map_lines(data, map, x);
	data->map = malloc(sizeof(char *) * (data->wholemap.height + 1));
	if (!data->map)
		return (error_msg("Create map fail", -1));
	if (fill_map_tab(&data->wholemap, data->map, x) == -1)
		return (-1);
	replace_space(data);
	return (0);
}

// Replace space into wall
static void	replace_space(t_data *data)
{
	int	x;
	int	y;
	int	start;
	int	end;

	x = -1;
	while (data->map[++x])
	{
		start = 0;
		while (data->map[x][start] && ft_isspace(data->map[x][start]))
			start++;
		end = start;
		while (data->map[x][end])
			end++;
		end--;
		while (end > start && ft_isspace(data->map[x][end]))
			end--;
		y = start;
		while (y <= end)
		{
			if (data->map[x][y] == ' ')
				data->map[x][y] = '1';
			y++;
		}
	}
}
