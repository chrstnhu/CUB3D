/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   error.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/08/13 10:30:50 by chrhu				#+#	#+#				*/
/*   Updated: 2024/08/19 16:08:36 by chrhu			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			error_exit(char *s);
void		clean_exit(t_data *data, char *error_message, int code);
static void	free_wholemap_file(char **wholemap_file);
static void	free_resources(t_data *data);

// Print red error message
int	error_msg(char *str, int error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n" DEF, 2);
	return (error);
}

// Print red error message and exit
int	error_exit(char *s)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n" DEF, 2);
	exit(EXIT_FAILURE);
}

// Clean and exit
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
	free_resources(data);
	exit(code);
}

// Free all ressources
static void	free_resources(t_data *data)
{
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
		free(data->mlx);
	}
}

// Free wholemap file
static void	free_wholemap_file(char **wholemap_file)
{
	int	i;

	i = 0;
	if (wholemap_file)
	{
		while (wholemap_file[i])
		{
			if (wholemap_file[i])
				free(wholemap_file[i]);
			i++;
		}
		free(wholemap_file);
	}
}
