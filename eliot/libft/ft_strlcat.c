/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:15:57 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 11:30:15 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (dest[n] != '\0')
	{
		n++;
	}
	while (src[i] != '\0' && n + i + 1 < size)
	{
		dest[n + i] = src[i];
		i++;
	}
	dest[n + i] = '\0';
	while (src[i] != '\0')
		i++;
	if (size < n)
		return (i + size);
	return (n + i);
}
