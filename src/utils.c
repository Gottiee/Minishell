/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:58:15 by eedy              #+#    #+#             */
/*   Updated: 2022/08/03 14:20:38 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

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
		count++;
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
