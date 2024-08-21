/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   error.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/13 10:30:50 by chrhu			 #+#	#+#			 */
/*   Updated: 2024/08/19 16:08:36 by chrhu			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_msg(char *str, int error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n" DEF, 2);
	return (error);
}

int	error_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

static void free_texinfo(t_texinfo *texinfo)
{
    if (texinfo->floor)
    {
        free(texinfo->floor);
        texinfo->floor = NULL;
    }

    if (texinfo->ceiling)
    {
        free(texinfo->ceiling);
        texinfo->ceiling = NULL;
    }

    if (texinfo->north)
    {
        free(texinfo->north);
        texinfo->north = NULL;
    }

    if (texinfo->south)
    {
        free(texinfo->south);
        texinfo->south = NULL;
    }

    if (texinfo->west)
    {
        free(texinfo->west);
        texinfo->west = NULL;
    }

    if (texinfo->east)
    {
        free(texinfo->east);
        texinfo->east = NULL;
    }
}

static void	free_map(char **map)
{
    if (map)
    {
        for (int i = 0; map[i]; i++)
            free(map[i]);
        free(map);
    }
}

static void	free_textures(void **textures, int count)
{
    if (textures)
    {
        for (int i = 0; i < count; i++)
        {
            if (textures[i])
                free(textures[i]);
        }
        free(textures);
    }
}

static void	free_wholemap_file(char **wholemap_file)
{
    if (wholemap_file)
    {
        for (int i = 0; wholemap_file[i]; i++)
            free(wholemap_file[i]);
        free(wholemap_file);
    }
}

void	clean_exit(t_data *data, char *error_message, int code)
{
    if (error_message)
    {
        if (!ft_strncmp("Window closed", error_message, 13))
            ft_putstr_fd(GREEN, 2);
        else
        {
            ft_putstr_fd(RED, 2);
            ft_putstr_fd("Error : ", 2);
        }
        ft_putstr_fd(error_message, 2);
        ft_putstr_fd("\n" DEF, 2);
    }
    // Free any allocated resources
    free_texinfo(&data->texinfo);
    if (data->texture_pixels)
        free_tab((void **)data->texture_pixels);

    if (data->textures)
        free_textures((void **)data->textures, 5);

    if (data->map)
        free_map(data->map);

    if (data->wholemap.file)
        free_wholemap_file(data->wholemap.file);

    if (data->mlx && data->win)
        mlx_destroy_window(data->mlx, data->win);

    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        mlx_loop_end(data->mlx);
    }
    free(data->mlx);

    // Add any other necessary cleanup here
    exit(code);
}