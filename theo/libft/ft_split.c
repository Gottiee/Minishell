/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:29:12 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 17:36:39 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_nb_word(char const *s, char c)
{
	int	res;
	int	word;

	res = 0;
	word = 0;
	while (*s)
	{
		if (*s == c && word)
		{
			res++;
			word = 0;
		}
		else if (*s != c && word == 0)
			word = 1;
		s++;
	}
	if (word == 1)
		res++;
	return (res);
}

static int	get_len_word(char const *s, char c, int index)
{
	int	res;
	int	word;

	res = 0;
	word = 0;
	while (index)
	{
		if (*s == c && word)
		{
			index--;
			word = 0;
		}
		else if (*s != c && word == 0)
			word = 1;
		s++;
	}
	while (*s == c)
		s++;
	while (*s != '\0' && *s++ != c)
		res++;
	return (res);
}

static const char	*get_pointer_word(char const *s, char c, int index)
{
	int	word;

	word = 0;
	while (index)
	{
		if (*s == c && word)
		{
			index--;
			word = 0;
		}
		else if (*s != c && word == 0)
			word = 1;
		s++;
	}
	while (*s == c)
		s++;
	return (s);
}

static void	free_all(char ***tabl)
{
	int	i;

	i = 0;
	while (*tabl[i] != NULL)
	{
		free(*tabl[i]);
		i++;
	}
	free(*tabl);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	int			nb_word;
	int			len_word;
	const char	*p_word;

	nb_word = get_nb_word(s, c);
	res = ft_calloc(nb_word + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (nb_word > 0)
	{
		len_word = get_len_word(s, c, nb_word - 1) + 1;
		res[nb_word - 1] = ft_calloc(len_word, sizeof(char));
		if (res[nb_word - 1] == NULL)
		{
			free_all(&res);
			return (NULL);
		}
		p_word = get_pointer_word(s, c, nb_word - 1);
		ft_strlcpy(res[nb_word - 1], p_word, len_word);
		nb_word--;
	}
	return (res);
}
