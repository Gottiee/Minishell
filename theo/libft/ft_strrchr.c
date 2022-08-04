/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:22:43 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 15:56:01 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	c = (unsigned char)c;
	if (str == NULL)
		return (NULL);
	i = ft_strlen((char *)str);
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)&(str[i]));
		i--;
	}
	return (NULL);
}
