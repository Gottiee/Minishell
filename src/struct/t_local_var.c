/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_local_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:12:35 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:07:33 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

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
t_lcl_var	*get_lclvar_by_name(t_lcl_var *lclvar, char *tofind)
{
	t_lcl_var	*res;

	res = NULL;
	if (lclvar)
	{
		res = lclvar;
		while (res)
		{
			if (ft_strnstr(res->name, tofind, ft_strlen(res->name)) != NULL)
				if (ft_strlen(res->name) == ft_strlen(tofind))
					break ;
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

t_lcl_var	*create_rtrn_val(void)
{
	t_lcl_var	*rtrn_val;
	char		*tmp;		

	rtrn_val = ft_calloc(1, sizeof(t_lcl_var));
	rtrn_val->next = NULL;
	tmp = ft_calloc(2, sizeof(char));
	tmp[0] = '?';
	rtrn_val->name = tmp;
	tmp = ft_calloc(2, sizeof(char));
	tmp[0] = '0';
	rtrn_val->val = tmp;
	return (rtrn_val);
}

t_lcl_var	*generate_envvar_list(char **envp)
{
	int					i;
	static t_lcl_var	*res;

	if (res == NULL)
	{
		i = 0;
		res = NULL;
		while (envp && envp[i] != NULL)
		{
			add_back_lclvar(&res, create_lclvar(envp[i]));
			i++;
		}
		add_back_lclvar(&res, create_rtrn_val());
	}
	return (res);
}
