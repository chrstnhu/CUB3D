/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/19 15:31:14 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	copy_cub_file(t_data *data);
static int	init_wholemap_file(t_data *data);

int	parse_cub_file(t_data *data, char *path)
{
	char	*line;
	int		fd;

	data->wholemap.path = path;
	data->wholemap.fd = open(path, O_RDONLY);
	fd = open(path, O_RDONLY);
	printf("parse_cub_file  data->wholemap.path:%s\n", data->wholemap.path);
	if (fd < 0 || data->wholemap.fd < 0)
		return (error_exit(RED"Error\nInvalid file"DEF));
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
			free(line);
		else
		{
			if (parse_line(data, line) == -1)
				return (error_exit(RED"Error\nInvalid parsing"DEF));
			free(line);
		}
		data->wholemap.line_count++;
		line = get_next_line(fd);
	}
	copy_cub_file(data);
	parse_map(data, data->wholemap.file);
	return (close(data->wholemap.fd), 0);
}

static void	copy_cub_file(t_data *data)
{
	int		i;
	int		col;
	int		row;
	char	*line;

	i = 0;
	col = 0;
	row = 0;
	line = get_next_line(data->wholemap.fd);
	if (init_wholemap_file(data) == -1)
		return ;
	while (line != NULL)
	{
		data->wholemap.file[row] = malloc((ft_strlen(line) + 1) * sizeof(char));
		if (!data->wholemap.file[row])
			return (free_tab((void **)data->wholemap.file));
		while (line[i] != '\0')
			data->wholemap.file[row][col++] = line[i++];
		data->wholemap.file[row++][col] = '\0';
		col = 0;
		i = 0;
		free(line);
		line = get_next_line(data->wholemap.fd);
	}
	data->wholemap.file[row] = NULL;
}

static int	init_wholemap_file(t_data *data)
{
	data->wholemap.file = malloc((data->wholemap.line_count \
			+ 1) * sizeof(char *));
	if (!(data->wholemap.file))
	{
		error_msg(RED"Error\nInvalid calloc"DEF, 0);
		return (-1);
	}
	return (0);
}
