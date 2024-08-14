/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:17:03 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/13 10:54:52 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dest = (char *)malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (0);
	while (s1[j] != '\0')
	{
		dest[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

// char	*ft_strjoin(char const *s1, char *s2)
// {
// 	char	*ptr;
// 	size_t	len_start;
// 	size_t	len_buff;

// 	if (!s1)
// 	{
// 		s1 = (char *)malloc(1);
// 		if (!s1)
// 			return (NULL);
// 		s1[0] = '\0';
// 	}
// 	len_start = ft_strlen(s1);
// 	len_buff = ft_strlen(s2);
// 	ptr = (char *)malloc(len_start + len_buff + 1);
// 	if (!ptr)
// 	{
// 		free(s1);
// 		return (NULL);
// 	}
// 	ft_memcpy(ptr, s1, len_start);
// 	ft_memcpy(ptr + len_start, buff, len_buff + 1);
// 	ptr[len_start + len_buff] = '\0';
// 	free(s1);
// 	return (ptr);
// }
