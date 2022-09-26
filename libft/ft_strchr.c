/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:28:53 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 15:54:54 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;
	int	len;

	c = (unsigned char)c;
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (i <= len)
	{
		if (str[i] == c)
			return ((char *)&(str[i]));
		i++;
	}
	return (NULL);
}
