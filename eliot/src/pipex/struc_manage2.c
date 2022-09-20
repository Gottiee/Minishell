/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc_manage2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:40:12 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 14:45:03 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	add_char_here_doc(t_str *start, char char_p)
{
	t_str	*new;
	t_str	*tmp;

	tmp = start;
	if (!tmp->c)
	{
		tmp->c = char_p;
		tmp->next = NULL;
		return (0);
	}
	new = malloc(sizeof(t_str));
	if (!new)
		return (-1);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	new->c = char_p;
	return (0);
}

char	*concatenate_tstr(t_str *node)
{
	t_str	*tmp;
	int		count_char;
	char	*str;
	int		i;

	i = -1;
	count_char = 0;
	tmp = node;
	while (tmp)
	{
		count_char ++;
		tmp = tmp->next;
	}
	str = malloc(sizeof(char) * count_char + 1);
	if (!str)
		return (NULL);
	str[count_char] = '\0';
	tmp = node;
	while (++i < count_char)
	{
		str[i] = tmp->c;
		tmp = tmp->next;
	}
	return (str);
}
