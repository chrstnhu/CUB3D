/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:22:36 by leochen           #+#    #+#             */
/*   Updated: 2024/09/20 13:08:32 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	release_texture(char **texture);
void		free_map(char **map);
void		free_textures(void **textures, int count);

// Free texture info
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
	release_texture(&texinfo->north);
	release_texture(&texinfo->south);
	release_texture(&texinfo->west);
	release_texture(&texinfo->east);
}

// Free texture
static void	release_texture(char **texture)
{
	if (*texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

// Free map
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

// Free textures
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
