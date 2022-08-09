/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:47:02 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/09 03:59:18 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

char	*remove_dquotes(char *str)
{
	t_str	*tstr;
	
	tstr = NULL;
	while (*str)
	{
		if (*str != '"')
			add_back_tstr(&tstr, create_tstr(*str));
		str++;
	}
	return (get_str_with_tstr(tstr));
}