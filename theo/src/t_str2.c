/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:06:19 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/22 16:06:54 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

int	tstr_len(t_str *tstr)
{
	int		res;
	t_str	*temp;

	res = 0;
	temp = tstr;
	while (temp)
	{
		res++;
		temp = temp->next;
	}
	return (res);
}
