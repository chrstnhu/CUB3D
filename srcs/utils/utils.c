/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   utils.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/08/13 10:30:50 by chrhu				#+#	#+#				*/
/*   Updated: 2024/08/19 13:58:15 by chrhu			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	jump_space(char **line);
char	*clean_spaces(const char *line);

// Free **tab
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

// Jump all the space
void	jump_space(char **line)
{
	while (ft_isspace(**line))
	{
		(*line)++;
	}
}

// Trim space at the start and at the end
void	trim(char **str)
{
	char	*start;
	char	*end;

	start = *str;
	while (*start == ' ' || *start == '\n' || *start == '\r' || *start == '\t')
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\n' || *end == '\r'
			|| *end == '\t'))
		end--;
	*(end + 1) = '\0';
	*str = start;
}

// Clean space of the color
char	*clean_spaces(const char *line)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	new_line = malloc(len + 1);
	if (!new_line)
		return (NULL);
	while (i < len && ft_isspace(line[i]))
		i++;
	while (i < len)
	{
		if (!ft_isspace(line[i]))
			new_line[j++] = line[i];
		i++;
	}
	if (j > 0 && ft_isspace((new_line[j - 1])))
		j--;
	new_line[j] = '\0';
	return (new_line);
}

// Initialize map elements
void	init_map_element(t_map_elements *elements)
{
	elements->north = 0;
	elements->south = 0;
	elements->west = 0;
	elements->east = 0;
	elements->floor = 0;
	elements->ceiling = 0;
}
