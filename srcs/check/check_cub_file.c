/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/21 18:49:28 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			check_cub_file(char *path);
//int			check_texture(char *line);
static int	path_valid(char *path);

int	file_valid(char *file)
{
	int	len;
	int fd;

	len = ft_strlen(file);
	if (ft_strncmp(&file[len - 4], ".cub", 4))
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (0);
}

// int	check_cub_file(char *path)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_putendl_fd("Error", 2);
// 		return (1);
// 		// return (error_exit(RED"Error\nInvalid file"DEF));
// 	}
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (line[0] == '\n')
// 			free(line);
// 		else
// 		{
// 			// printf("2. Before check_texture\n");
// 			if (check_texture(line) == -1)
// 			{
// 				//printf("line checked is %s and check_texture returned %d\n", line, check_texture(line));
// 				return (error_exit(RED"Error\nInvalid texture"DEF));
// 			}			
// 			free(line);
// 		}
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }



int	check_cub_file(char *path)
{
	int		fd;
	char	*line;
	texinfo elements = {0, 0, 0, 0, 0, 0}; // Initialize all elements as not found

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
		}
		else
		{
			if (checkk_texture(line, &elements) == -1)
			{
				get_next_line(-42);
				free(line);
				close(fd);
				return (error_exit(RED"Error\nInvalid texture or color"DEF));
			}			
			free(line);
		}
		line = get_next_line(fd);
	}

	close(fd);

	// After processing all lines, check if all required elements are present
	if (validate_map(&elements) == -1)
	{
		return (error_exit(RED"Error\nMissing required map elements"DEF));
	}

	return (0);
}


// int	check_texture(char *line)
// {
// 	// printf("3. Check texture\n");
// 	jump_space(&line);
// 	// printf("-> before line :(%s)\n", line);
// 	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
// 		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
// 	{
// 		line += 2;// Move the pointer past the identifier ("NO", "SO", etc.)
// 		jump_space(&line);// Jump over any spaces after the identifier
// 		// printf("-> after line  :(%s)\n", line);
// 		if (path_valid(line) == -1)
// 			return (-1);
// 		return (0);// Successfully processed a texture line, return success
// 	}
// 	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
// 	{
// 		line += 2;
// 		jump_space(&line);// Move the pointer past the identifier ("F", "C")
// 		if ((check_digit(line) == -1))
// 			return (-1);
// 		if ((check_color(line) == -1))
// 			return (-1);
// 		return (0);// Successfully processed a color line, return success
// 	}
// 	return (0);/* -1 change to 0*/
// }

 int checkk_texture(char *line, texinfo *elements)
{
    jump_space(&line);

    if (!ft_strncmp(line, "NO ", 3))
    {
        elements->north = 1;
        line += 2;
        jump_space(&line);
        if (path_valid(line) == -1)
            return (-1);
    }
    else if (!ft_strncmp(line, "SO ", 3))
    {
        elements->south = 1;
        line += 2;
        jump_space(&line);
        if (path_valid(line) == -1)
            return (-1);
    }
    else if (!ft_strncmp(line, "WE ", 3))
    {
        elements->west = 1;
        line += 2;
        jump_space(&line);
        if (path_valid(line) == -1)
            return (-1);
    }
    else if (!ft_strncmp(line, "EA ", 3))
    {
        elements->east = 1;
        line += 2;
        jump_space(&line);
        if (path_valid(line) == -1)
            return (-1);
    }
    else if (!ft_strncmp(line, "F ", 2))
    {
        elements->floor = 1;
        line += 2;
        jump_space(&line);
        if (check_digit(line) == -1)
            return (-1);
        if (check_color(line) == -1)
            return (-1);
    }
    else if (!ft_strncmp(line, "C ", 2))
    {
        elements->ceiling = 1;
        line += 2;
        jump_space(&line);
        if (check_digit(line) == -1)
            return (-1);
        if (check_color(line) == -1)
            return (-1);
    }
    return (0); // Return 0 to indicate this line was processed successfully.
}

int validate_map(texinfo *elements)
{
    if (!elements->north || !elements->south || !elements->west || !elements->east || !elements->floor || !elements->ceiling)
    {
        // If any element is missing, return an error
        return (-1);
    }
    return (0); // All elements are present, return success
}


static int	path_valid(char *path)
{
	// printf("4. Check path\n");
	int	len;

	trim(&path);
	len = ft_strlen(path);
	//printf("Path :(%s), len : %d\n\n", path, len);
	if (ft_strnstr(path, ".xpm", len) == NULL)
	{
		//printf(RED"Error\ntexture path not end with .xpm\n"DEF);
		return (-1);
	}
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		//printf("in path_valid(), the path opended with error is  %s\n", path);
		//printf(RED"Error\nInvalid texture path\n"DEF);
		return (-1);
	}
	close(fd);
	return (0);
}

/*  这个是mcombeau检查texture的函数
int	check_file(char *arg, bool cub)
{
	int	fd;

	if (is_dir(arg))
		return (err_msg(arg, ERR_FILE_IS_DIR, FAILURE));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, strerror(errno), FAILURE));
	close(fd);
	if (cub && !is_cub_file(arg))
		return (err_msg(arg, ERR_FILE_NOT_CUB, FAILURE));
	if (!cub && !is_xpm_file(arg))
		return (err_msg(arg, ERR_FILE_NOT_XPM, FAILURE));
	return (SUCCESS);
}*/   
     