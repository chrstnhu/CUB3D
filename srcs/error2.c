/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:22:36 by leochen           #+#    #+#             */
/*   Updated: 2024/08/22 15:30:39 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_texture(char **texture)
{
	if (*texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

void	free_texinfo(t_texinfo *texinfo)
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
	free_texture(&texinfo->north);
	free_texture(&texinfo->south);
	free_texture(&texinfo->west);
	free_texture(&texinfo->east);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			if (map[i])
				free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_textures(void **textures, int count)
{
	int	i;

	i = 0;
	if (textures)
	{
		while (i < count)
		{
			if (textures[i])
				free(textures[i]);
			i++;
		}
		free(textures);
	}
}
