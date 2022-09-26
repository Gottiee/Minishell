/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:08:57 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 11:33:47 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_len_int(int n)
{
	int	res;

	res = 0;
	if (n < 0)
		res ++;
	while (n != 0)
	{
		res++;
		n /= 10;
	}
	if (res == 0)
		return (1);
	return (res);
}

static char	get_char_index(int n, int i)
{
	char	res;
	int		to_div;

	if (n < 0 && i == 0)
		return ('-');
	to_div = get_len_int(n) - i - 1;
	while (to_div-- > 0)
		n /= 10;
	if (n < -10)
		n += 10;
	if (n < 0)
		n *= -1;
	res = (n % 10) + 48;
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		i;

	len = get_len_int(n);
	res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = get_char_index(n, i);
		i++;
	}
	return (res);
}
