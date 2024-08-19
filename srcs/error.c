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

void	clean_exit(t_data *data, char *error_message, int code)
{
	if (error_message)
	{
		if (!ft_strncmp("Window closed", error_message, 13))
			ft_putstr_fd(GREEN, 2);
		else
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("Error :", 2);
		}
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd("\n" DEF, 2);
	}
	// Free any allocated resources
	if (data->texture_pixels)
		free_tab((void **)data->texture_pixels);

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
