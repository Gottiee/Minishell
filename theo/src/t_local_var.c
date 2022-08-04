/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_local_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:12:35 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/04 19:57:55 by tokerman         ###   ########.fr       */
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

char	*get_text_val(char *cmd)
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
	return (get_str_with_tstr(tstr));
}

int		get_type_val(char *text)
{
	while (*text)
	{
		if (ft_isdigit(*text) == 0)
			return (1);
		text++;
	}
	return (0);
}

void	free_lclvar(t_lcl_var *var)
{
	free(var->name);
	free(var->val);
	free(var);
}

/*
prendre en compte les operations
*/
t_lcl_var	*create_lclvar(char	*cmd)
{
	t_lcl_var	*res;
	
	res = ft_calloc(1, sizeof(t_lcl_var));
	res->next = NULL;
	res->name = get_name_var(cmd);
	res->val = get_text_val(cmd);
	res->type = get_type_val(res->val);
	return (res);
}