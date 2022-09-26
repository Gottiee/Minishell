/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_local_var2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:43:42 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:07:36 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

/*
recupere juste le nom de la viariable dans la commande
exemple:
	ok=89
	retourne (ok)
*/
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

/*
recupere juste la valeur de la viariable dans la commande
exemple:
	ok=89
	retourne (89)
*/
char	*get_text_val(char *cmd)
{
	t_str	*tstr;
	int		quotes;

	tstr = NULL;
	while (*cmd == ' ')
		cmd++;
	while (*cmd != '=')
		cmd++;
	cmd++;
	quotes = 0;
	while (*cmd && (*cmd != ' ' || quotes != 0))
	{
		if (*cmd == '\'' || *cmd == '"')
		{
			if (quotes)
				quotes = 0;
			else
				quotes = *cmd;
		}
		add_back_tstr(&tstr, create_tstr(*cmd));
		cmd++;
	}
	return (get_str_with_tstr(tstr));
}

/*
retourne le type de donnees que la variable va stocker
1 = string 
0 = long long int
*/
int	get_type_val(char *text)
{
	while (*text)
	{
		if (ft_isdigit(*text) == 0)
			return (1);
		text++;
	}
	return (0);
}

/*
free la liste chainee var
*/
void	free_lclvar(t_lcl_var *var)
{
	if (var)
	{
		if (var->next)
			free_lclvar(var->next);
		free(var->name);
		free(var->val);
		free(var);
	}
}

/*
creer la variable local a partir de la cmd en 
	recuperant le nom, la valeur et le type de valeur
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
