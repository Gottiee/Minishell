/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:11:17 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 11:11:39 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (d < s)
	{
		while (size--)
			*d++ = *s++;
	}
	else
	{
		while (size-- > 0)
			d[size] = s[size];
	}
	return (dest);
}
