/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:29:36 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/22 15:51:54 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_printf_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_printf_str("(null)"));
	while (str[i] != '\0')
	{
		ft_printf_char (str[i]);
		i++;
	}
	return (i);
}
