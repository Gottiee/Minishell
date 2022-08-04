/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:34:15 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/04 18:48:57 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

t_str	*create_tstr(char c)
{
	t_str	*res;

	res = ft_calloc(1, sizeof(t_str));
	res->c = c;
	res->next = NULL;
	return (NULL);
}

void	add_back_tstr(t_str **first, t_str *new)
{
	t_str	*temp;

	if (first && *first)
	{
		temp = *first;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else if (first)
		*first = new;
}

void	free_tstr(t_str *tstr)
{
	if (tstr->next)
		free_all_pipex(tstr->next);
	free(tstr);
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