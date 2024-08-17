/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:50 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/17 19:34:08 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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

void	jump_space(char	*line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
	{
		line++;
		i++;
	}
}
