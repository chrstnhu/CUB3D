/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:21:38 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/22 15:51:08 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	ft_check(char const *s1, char const set)
{
	size_t	i;

	i = 0;
	if (!s1[i])
		return (0);
	while (s1[i] != '\0')
	{
		if (s1[i] == set)
			return (1);
		s1++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*result;

	i = 0;
	start = 0;
	while (s1[start] && ft_check(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (start < end && ft_check(set, s1[end - 1]))
		end--;
	len = end - start;
	result = (char *) malloc (sizeof(char) * len + 1);
	if (!result)
		return (0);
	while (start + i < end)
	{
		result[i] = s1[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
