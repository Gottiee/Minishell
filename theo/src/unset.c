/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:41:36 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/21 13:05:43 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

void	copy_envvar(t_lcl_var *dest, t_lcl_var *src)
{
	src = dest->next;
	free(dest->name);
	free(dest->val);
	dest->name = ft_strdup(src->name);
	dest->val = ft_strdup(src->val);
	dest->next = src->next;
	src->next = NULL;
	free_lclvar(src);
}

t_lcl_var	*remove_envvar_by_name(t_lcl_var *env_lst, char *name)
{
	t_lcl_var	*temp;
	t_lcl_var	*prev;

	prev = NULL;
	temp = env_lst;
	while (temp)
	{
		if (ft_strnstr(temp->name, name, ft_strlen(temp->name)) == temp->name
			&& ft_strlen(name) == ft_strlen(temp->name))
		{
			if (prev == NULL)
				copy_envvar(temp, prev);
			else
			{
				prev->next = temp->next;
				temp->next = NULL;
				free_lclvar(temp);
			}
			return (env_lst);
		}
		prev = temp;
		temp = temp->next;
	}
	return (env_lst);
}

int	cmd_unset(char **cmd_tab_exec)
{
	int			i;
	char		*temp;
	t_lcl_var	*env_lst;

	if (cmd_tab_exec && *cmd_tab_exec)
	{
		env_lst = generate_envvar_list(NULL);
		i = 1;
		temp = cmd_tab_exec[i];
		while (temp != NULL)
		{
			env_lst = remove_envvar_by_name(env_lst, temp);
			temp = cmd_tab_exec[++i];
		}
	}
	return (0);
}
