/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: chrhu <chrhu@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/13 10:30:50 by chrhu			 #+#	#+#			 */
/*   Updated: 2024/08/19 13:58:15 by chrhu			###   ########.fr	   */
/*																			*/
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

void jump_space(char **line)
{
	while (ft_isspace(**line))
	{
		(*line)++;
	}
}

void trim(char **str)
{
	char *start;
	char *end;

	start = *str;
	// Trim start (leading spaces)
	while (*start == ' ' || *start == '\n' || *start == '\r'
		|| *start == '\t')
		start++;

	// Trim end (trailing spaces)
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\n'
		|| *end == '\r' || *end == '\t'))
		end--;

	// Write the new null terminator
	*(end + 1) = '\0';

	// Update the original string pointer to the trimmed version
	*str = start;
}
