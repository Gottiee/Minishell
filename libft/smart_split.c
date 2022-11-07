/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:33:46 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/07 17:10:01 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	sp_nb_wrd(char *str)
{
	int		nb_word;
	char	*tmp;
	int		quotes;

	nb_word = 1;
	tmp = str;
	quotes = 0;
	while (tmp && *tmp)
	{
		if (quotes == 0 && (*tmp == '\'' || *tmp == '"' || *tmp == '`'))
			quotes = *tmp;
		else if (*tmp == quotes)
			quotes = 0;
		else if (*tmp == ' ' && quotes == 0 && tmp != str && *(tmp - 1) != ' ')
			nb_word++;
		tmp++;
	}
	return (nb_word);
}

char	**sub_smart_split(char *str, int nb_word, char *tmp, int quotes)
{
	char	**res;
	t_str	*tstr;

	res = ft_calloc(sp_nb_wrd(str) + 1, sizeof(char *));
	tstr = NULL;
	while (tmp && *tmp)
	{
		if (quotes == 0 && (*tmp == '\'' || *tmp == '"' || *tmp == '`'))
			quotes = *tmp;
		else if (*tmp == quotes)
			quotes = 0;
		else if (*tmp == '|' && quotes == 0 && tmp != str && *(tmp - 1) != '|')
		{
			res[nb_word++] = get_str_from_tstr(tstr);
			tstr = NULL;
		}
		else
			add_back_tstr(&tstr, new_tstr(*tmp));
		tmp++;
	}
	if (tstr)
		res[nb_word] = get_str_from_tstr(tstr);
	return (res);
}

char	**smart_split(char *str)
{
	int		nb_word;
	char	*tmp;
	int		quotes;

	if (str == NULL || *str == '\0')
		return (NULL);
	nb_word = 0;
	tmp = str;
	quotes = 0;
	return (sub_smart_split(str, nb_word, tmp, quotes));
}
