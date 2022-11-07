/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:36:04 by tokerman          #+#    #+#             */
/*   Updated: 2022/11/07 17:11:28 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str	*new_tstr(char c)
{
	t_str	*res;

	res = ft_calloc(1, sizeof(t_str));
	res->c = c;
	res->next = NULL;
	return (res);
}

void	add_back_tstr(t_str **list, t_str *new)
{
	t_str	*tmp;

	if (list)
	{
		if (*list)
		{
			tmp = *list;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*list = new;
	}
}

void	free_tstr(t_str *tstr)
{
	if (tstr != NULL)
	{
		if (tstr->next != NULL)
			free_tstr(tstr->next);
		free(tstr);
	}
}

char	*get_str_from_tstr(t_str *tstr)
{
	t_str	*tmp;
	int		len;
	char	*res;

	len = 0;
	tmp = tstr;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	res = ft_calloc(len + 1, sizeof(char));
	len = 0;
	tmp = tstr;
	while (tmp)
	{
		res[len++] = tmp->c;
		tmp = tmp->next;
	}
	free_tstr(tstr);
	return (res);
}
