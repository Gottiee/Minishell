/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_trad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:39:31 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/27 20:39:31 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

/*
retourne la chaine de charactere correspondant au nom de la var
cette chaine de charactere et delimiter par un charactere speciale ou la fin de la ligne
*/
char	*get_var_name(char *cmd)
{
	t_str	*tstr;
	char	*start;

	tstr = NULL;
	start = cmd;
	while (*cmd && (ft_isalnum(*cmd) || *cmd == '_'))
	{
		add_back_tstr(&tstr, create_tstr(*cmd));
		cmd++;
	}
	if (start == cmd)
		return (NULL);
	return (get_str_with_tstr(tstr));
}

/*
cherche dans les variables locale et environnementale avec le nim de la variable
	et retourne la valeur de cette derniere si elle existe et retourne NULL
		si elle n'existe pas
*/
t_str	*get_var_val(char *cmd, t_lcl_var **lclvar, t_lcl_var **envvar)
{
	char	*name;
	t_lcl_var *temp_lcl;
	t_lcl_var *temp_env;

	name = get_var_name(cmd);
	temp_lcl = get_lclvar_by_name(lclvar, name);
	temp_env = get_lclvar_by_name(envvar, name);
	if (temp_env)
		return (get_tstr_with_str(temp_env->val));
	if(temp_lcl)
		return (get_tstr_with_str(temp_lcl->val));
	return (NULL);
}

/*
traduit les variables dans une chaine de charactere donnée
*/
char	*get_txt(char *cmd, t_lcl_var **lclvar, t_lcl_var **envvar)
{	
	t_str	*tstr;
	int		quotes;

	tstr = NULL;
	quotes = 0;
	while (*cmd)
	{
		if (quotes == 0 && (*cmd == '"' || *cmd == '\''))
		{
			quotes = *(cmd++);
			continue;
		}
		else if (quotes > 0 && *cmd == quotes)
		{
			quotes = 0;
			continue;
		}
		else if (*cmd == ' ' && quotes == 0)
			break;
		if (quotes == '\'' || *cmd != '$')
			add_back_tstr(&tstr, create_tstr(*cmd++));
		else
		{
			cmd++;
			add_back_tstr(&tstr, get_var_val(cmd, lclvar, envvar));
			while (*cmd && (ft_isalnum(*cmd) || *cmd == '_'))
				cmd++;
		}
	}
	return (get_str_with_tstr(tstr));
}