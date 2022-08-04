/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:06:45 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 11:07:35 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void			*res;
	void			*temp;
	unsigned int	i;

	res = malloc(size * count);
	if (res == NULL)
		return (NULL);
	temp = res;
	i = 0;
	while (i < count * size)
	{
		*((char *)temp++) = 0;
		i++;
	}
	return (res);
}
