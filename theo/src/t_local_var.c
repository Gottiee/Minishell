/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_local_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:12:35 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/19 18:10:43 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

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
{// traduire les variables ex : ok=$test*8	
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
creer la variable local a partir de la cmd en recuperant le nom, la valeur et le type de valeur
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

/*
ajoute l'element new a la fin de la liste chainee first
*/
void	add_back_lclvar(t_lcl_var **first, t_lcl_var *new)
{
	t_lcl_var	*temp;

	if (first)
	{
		if (*first)
		{
			temp = *first;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new;
		}
		else
			*first = new;
	}
}

/*
retourne l'element de la liste chainee lclvar qui a le meme nom que tofind
si il n'y en pas dans la liste chainee, retourne null
*/
t_lcl_var	*get_lclvar_by_name(t_lcl_var **lclvar, char *tofind)
{
	t_lcl_var	*res;

	res = NULL;
	if (lclvar)
	{
		res = *lclvar;
		while (res)
		{
			if (ft_strnstr(res->name, tofind, ft_strlen(res->name)) != NULL)
				if (ft_strlen(res->name) == ft_strlen(tofind))
					break;
			res = res->next;
		}
	}
	return (res);
}

void	change_envvar_val(char *name, char *new_val)
{
	t_lcl_var	*temp;
	t_lcl_var	*var;

	var = generate_envvar_list(NULL);
	temp = var;
	while (temp)
	{
		if (ft_strnstr(temp->name, name, ft_strlen(temp->name)) == temp->name
			&& ft_strlen(name) == ft_strlen(temp->name))
		{
			free(temp->val);
			temp->val = ft_strdup(new_val);
			return ;
		}
		temp = temp->next;
	}
}
