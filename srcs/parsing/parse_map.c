/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/14 19:58:24 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
static int print_map(char **map, int i, int j)
{
    // printf("Processing map section:\n");
    
    // Imprimer le contenu de la carte
    while (map[i] != NULL)
    {
        while (map[i][j] != '\0')
        {
            printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
        j = 0; // Réinitialiser la colonne pour la prochaine ligne
    }
    return (0);
}
*/

static void find_space_range(char *line, int *start, int *end)
{
	int j;
	int line_length;

	*start = -1;
	*end = -1;
	j = 0;
	line_length = 0;
	while (line[line_length])
		line_length++;
	while (line[j])
	{
		if (ft_isspace(line[j]) && *start == -1
			&& j > 0 && !ft_isspace(line[j - 1]))
			*start = j; // Find the start of the range of spaces surrounded by numbers
		else if (!ft_isspace(line[j]) && *start != -1
			&& j < line_length - 1 && !ft_isspace(line[j + 1]))
		{
			*end = j; // Find the end of the range of spaces surrounded by numbers
			break;
		}
		j++;
	}
	// If the line ends with spaces surrounded by numbers
	if (*start != -1 && *end == -1 && j > 0 && !ft_isspace(line[j - 1]))
		*end = j;
}

static void replace_space(t_data *data)
{
	int i;
	int j;
	int start;
	int end;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		find_space_range(data->map[i], &start, &end);
		// Debugging to check the values ​​of start and end
		// printf("Line %d: start = %d, end = %d\n", i, start, end);
		if (start != -1 && end != -1)
		{
			j = start;
			while (j < end)
			{
				if (data->map[i][j] == ' ')
					data->map[i][j] = '1'; // Replacce by wall :'1'
				j++;
			}
		}
		i++;
	}
	// print_map(data->map, 0, 0);
}

static int create_map(t_data *data, char **map, int i)
{
	printf("Create map :\n");
	data->wholemap.height = count_map_lines(data, map, i);
	data->map = malloc(sizeof(char *) * (data->wholemap.height + 1));
	if (!data->map)
		return (error_msg("Create map fail", -1));
	if (fill_map_tab(&data->wholemap, data->map, i) == -1)
		return (-1);
	replace_space(data);
	return (0);
}

static int get_map(t_data *data, char **map, int i, int j)
{
	while (map[i] != NULL)
	{
		while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
			j++;
		if (ft_isdigit((unsigned char)map[i][j]))
		{
			j = 0;
			// printf("Found map section and count %d\n", data->wholemap.height);
			// printf("Found map section and count %d\n", data->wholemap.index_end_of_map);
			//print_map(map, i, j);
			if (create_map(data, map, i) == -1)
			 	return (error_msg(data->wholemap.path, -1));
			else
				break;
		}
		i++;
		j = 0;
	}
	return (0);
}


int parse_map(t_data *data, char **map)
{
	printf("Parse map\n");
	int i;
	int j;
	int ret;

	ret = 0;
	i = 0;	
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = get_map(data, map, i, j);
			if (ret == -1)
				return (-1);
			else
				return (0);
			j++;
		}
		i++;
	}
	return (0);
}
