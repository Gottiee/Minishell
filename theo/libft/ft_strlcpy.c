/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:23:14 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 11:23:33 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	count;

	count = 0;
	while (src[count] != '\0')
	{
		count++;
	}
	if (count + 1 < size)
	{
		ft_strncpy(dest, src, count + 1);
	}
	else if (size > 0)
	{
		ft_strncpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (count);
}
