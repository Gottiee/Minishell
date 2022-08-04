/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:39:25 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/04 18:54:13 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

char	*get_name_var(char	*cmd)
{
	t_str	*tstr;
	
	tstr = NULL;
	while (*cmd == ' ')
		cmd++;
	while (*cmd != '=')
	{
		add_back_tstr(&tstr, create_tstr(*cmd));
		cmd++;
	}
	return (get_str_with_tstr(tstr));
}

int	get_type_val(char *cmd)
{
	t_str	*tstr;
	int		quotes;
	
	tstr = NULL;
	quotes = 0;
	while (*cmd == ' ')
		cmd++;
	while (*cmd != '=')
		cmd++;
	cmd++;
	if (*cmd == '"' || *cmd == '\'')
		quotes = *(cmd++) - 33;
	while (*cmd)
	{
		if ((*cmd == '"' || *cmd == '\'') && quotes == *cmd - 33)
			break;
		add_back_tstr(&tstr, create_tstr(*cmd));
		cmd++;
	}
}

t_lcl_var	*create_lclvar(char	*cmd)
{
	t_lcl_var	*res;
	
	res = ft_calloc(1, sizeof(t_lcl_var));
	res->next = NULL;
	res->name = get_name_var(cmd);
}