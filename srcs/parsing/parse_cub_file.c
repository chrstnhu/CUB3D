/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/20 16:54:03 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_lines(t_data *data, int fd);
static void	copy_cub_file(t_data *data);
static int	init_wholemap_file(t_data *data);

// Open cub file
static int	open_cub_file(t_data *data, char *path)
{
	data->wholemap.path = path;
	data->wholemap.fd = open(path, O_RDONLY);
	if (data->wholemap.fd < 0)
		return (error_exit("Invalid file"));
	return (0);
}

// Parse the content of cub file
int	parse_cub_file(t_data *data, char *path)
{
	int	fd;

	if (open_cub_file(data, path) == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_exit("Invalid file"));
	if (parse_lines(data, fd) == -1)
		return (-1);
	copy_cub_file(data);
	parse_map(data, data->wholemap.file);
	return (close(data->wholemap.fd), 0);
}

// Parse each line in the file
static int	parse_lines(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && parse_line(data, line) == -1)
		{
			get_next_line(-42);
			free(line);
			clean_exit(data, RED"Error\nInvalid line"DEF, 1);
		}
		free(line);
		data->wholemap.line_count++;
		line = get_next_line(fd);
	}
	return (0);
}

// Copy the content of cub file in a new file
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
		data->wholemap.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
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

// Initialize the whole map file
static int	init_wholemap_file(t_data *data)
{
	data->wholemap.file = malloc((data->wholemap.line_count + 1)
			* sizeof(char *));
	if (!(data->wholemap.file))
	{
		error_msg(RED "Error\nInvalid calloc" DEF, 0);
		return (-1);
	}
	return (0);
}
