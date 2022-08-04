/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:02:38 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 11:04:11 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	negative;
	int	res;

	negative = 1;
	res = 0;
	while ((8 < *str && *str < 14) || *str == 32)
		str++;
	if (*str == '-' )
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			break ;
		res *= 10;
		res += negative * (*str - 48);
		str++;
	}
	return (res);
}
