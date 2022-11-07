/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trad_dquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:09:56 by tokerman          #+#    #+#             */
/*   Updated: 2022/10/24 16:36:19 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

int	thereis_file(t_str **tstr)
{
	int		file;
	t_str	*tmp;

	file = 0;
	if (tstr && *tstr)
	{
		tmp = *tstr;
		while (tmp)
		{
			if (tmp->c == '<' || tmp->c == '>')
				file = 1;
			else if (tmp->c != ' ')
				file = 0;
			tmp = tmp->next;
		}
	}
	return (file);
}

void	add_two_squote(t_str **tstr)
{
	add_back_tstr(tstr, create_tstr('\''));
	add_back_tstr(tstr, create_tstr('\''));
}

int	trad_after_file(char *cmd, t_str **tstr)
{
	char		*name;
	t_lcl_var	*temp_env;
	t_lcl_var	*envvar;
	int			res;

	if (thereis_file(tstr) == 0)
		return (0);
	envvar = generate_envvar_list(NULL);
	name = get_var_name(cmd + 1);
	if (name == NULL)
		return (0);
	temp_env = get_lclvar_by_name(envvar, name);
	res = 1 + ft_strlen(name);
	free(name);
	if (temp_env)
	{
		name = add_quotes(temp_env->val);
		add_back_tstr(tstr, get_tstr_with_str(name));
		free(name);
	}
	else
		add_two_squote(tstr);
	return (res);
}

char	*add_quotes(char *cmd)
{
	t_str	*tstr;

	tstr = NULL;
	while (cmd && *cmd)
	{
		if (ft_isalnum(*cmd) == 1)
			add_back_tstr(&tstr, create_tstr(*cmd++));
		else
		{
			if (*cmd == '\'')
				add_back_tstr(&tstr, create_tstr('"'));
			else
				add_back_tstr(&tstr, create_tstr('\''));
			add_back_tstr(&tstr, create_tstr(*cmd));
			if (*cmd == '\'')
				add_back_tstr(&tstr, create_tstr('"'));
			else
				add_back_tstr(&tstr, create_tstr('\''));
			cmd++;
		}	
	}
	return (get_str_with_tstr(tstr));
}

int	trad_dollar(char *cmd, t_str **tstr)
{
	char	*var_name;
	int		toadd;
	int		res;

	res = 0;
	toadd = trad_after_file(cmd, tstr);
	if (toadd > 0)
	{
		cmd += toadd;
		res += toadd;
		return (res);
	}
	else if ((*(cmd + 1) == '\0' || *(cmd + 1) == ' '
			|| !(ft_isalnum(*(cmd + 1)) || *(cmd + 1) == '_'))
		&& *(cmd + 1) != '?')
	{
		add_back_tstr(tstr, create_tstr(*cmd));
		return (1);
	}
	cmd++;
	add_back_tstr(tstr, get_var_val(cmd, 1));
	var_name = get_var_name(cmd);
	res += 1 + ft_strlen(var_name);
	free(var_name);
	return (res);
}
