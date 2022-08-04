/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:19:29 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 18:05:58 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*error(const char *s1, const char *s2)
{
	if (s2 == NULL || s1 == NULL )
		return ((char *)s1);
	if (ft_strncmp(s1, "", 1) == 0 && ft_strncmp(s2, "", 1) == 0)
		return ((char *)s1);
	return (NULL);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	s2len;
	unsigned int	i;
	unsigned int	j;

	if (error(s1, s2) != NULL)
		return (error(s1, s2));
	s2len = ft_strlen(s2);
	if (s2len > n)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i + s2len <= n)
	{
		j = 0;
		while (1)
		{
			if (s2[j] != '\0' && s1[i + j] != s2[j])
				break ;
			if (s2[j] == '\0')
				return ((char *)&s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
