/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:16:23 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 17:32:10 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	l;

	l = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	if (len < l)
		l = len;
	res = ft_calloc(l + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, &(s[start]), l + 1);
	return (res);
}
