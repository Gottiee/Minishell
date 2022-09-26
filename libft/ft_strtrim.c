/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:20:58 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 12:11:44 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	char_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

static int	get_len(char const *s1, char const *set)
{
	int	res;
	int	i;

	i = 0;
	res = ft_strlen(s1);
	while (res > 0 && char_in_set(s1[res - 1], set) == 1)
	{
		res--;
	}
	while (res > 0 && char_in_set(s1[i], set) == 1)
	{
		res--;
		i++;
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	int			i;
	int			len;

	len = get_len(s1, set);
	res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (char_in_set(*s1, set) == 1)
		s1++;
	i = 0;
	while (i < len)
		res[i++] = *s1++;
	return (res);
}
