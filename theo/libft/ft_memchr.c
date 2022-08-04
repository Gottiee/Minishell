/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:11:50 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/12 15:35:15 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int c, size_t size)
{
	char			*mem;
	unsigned int	i;

	c = (unsigned char)c;
	mem = (char *)memoryBlock;
	if (memoryBlock == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (mem[i] == c)
			return (&(mem[i]));
		i++;
	}
	return (NULL);
}
