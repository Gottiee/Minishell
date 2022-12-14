/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:34:15 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:07:41 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

t_str	*create_tstr(char c)
{
	t_str	*res;

	res = ft_calloc(1, sizeof(t_str));
	res->c = c;
	res->next = NULL;
	return (res);
}

char	*get_str_with_tstr(t_str *first)
{
	int		size;
	t_str	*temp;
	char	*res;

	size = 0;
	temp = first;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	res = ft_calloc(size + 1, sizeof(char));
	size = 0;
	temp = first;
	while (temp)
	{
		res[size] = temp->c;
		size++;
		temp = temp->next;
	}
	free_tstr(first);
	return (res);
}

t_str	*get_tstr_with_str(char *txt)
{
	t_str	*res;

	res = NULL;
	while (*txt)
	{
		add_back_tstr(&res, create_tstr(*txt));
		txt++;
	}
	return (res);
}
