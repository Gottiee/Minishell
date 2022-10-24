/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_trad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:39:31 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:07:16 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

/*
retourne la chaine de charactere correspondant au nom de la var
cette chaine de charactere et delimiter par un 
charactere speciale ou la fin de la ligne
*/
char	*get_var_name(char *cmd)
{
	t_str	*tstr;
	char	*start;

	tstr = NULL;
	start = cmd;
	if (*cmd == '?')
	{
		start = ft_calloc(2, sizeof(char));
		start[0] = '?';
		return (start);
	}
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
t_str	*get_var_val(char *cmd, int addquotes)
{
	char		*name;
	t_lcl_var	*temp_env;
	t_lcl_var	*envvar;
	t_str		*res;

	envvar = generate_envvar_list(NULL);
	name = get_var_name(cmd);
	temp_env = get_lclvar_by_name(&envvar, name);
	free(name);
	if (temp_env)
	{
		if (addquotes == 0)
			return (get_tstr_with_str(temp_env->val));
		name = add_quotes(temp_env->val);
		res = get_tstr_with_str(name);
		free(name);
		return (res);
	}
	return (NULL);
}

/*
traduit les variables dans une chaine de charactere donnée
*/
char	*get_txt(char *cmd)
{	
	t_str	*tstr;

	tstr = NULL;
	while (*cmd)
	{
		if (*cmd != '$')
			add_back_tstr(&tstr, create_tstr(*cmd++));
		else
		{
			if ((*(cmd + 1) == '\0' || *(cmd + 1) == ' '
			|| !(ft_isalnum(*(cmd + 1)) || *(cmd + 1) == '_'))
				&& *(cmd + 1) != '?')
				add_back_tstr(&tstr, create_tstr(*cmd++));
			else
			{
				char	*var_name;

				cmd++;
				add_back_tstr(&tstr, get_var_val(cmd, 0));
				var_name = get_var_name(cmd);
				cmd += ft_strlen(var_name);
				free(var_name);
			}
		}
	}
	return (get_str_with_tstr(tstr));
}

void	quotes_hrdc(char *cmd, int *quotes, int *hrdc)
{
	if (*quotes == 0 && (*cmd == '"' || *cmd == '\''))
		*quotes = *cmd;
	else if (*quotes > 0 && *cmd == *quotes)
		*quotes = 0;
	if (*cmd == '<' && *(cmd + 1) == '<')
		*hrdc = 1;
	else if (*hrdc && *cmd == ' ' && *(cmd - 1) != '<')
		*hrdc = 0;
}

char	*trad_cmd(char *cmd)
{
	t_str	*tstr;
	int		quotes;
	int		hrdc;

	tstr = NULL;
	quotes = 0;
	hrdc = 0;
	while (*cmd)
	{
		quotes_hrdc(cmd, &quotes, &hrdc);
		if (quotes == '\'' || *cmd != '$' || hrdc)
			add_back_tstr(&tstr, create_tstr(*(cmd++)));
		else
			cmd += trad_dollar(cmd, &tstr);
	}
	return (get_str_with_tstr(tstr));
}
