/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:30:54 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:06:47 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

int	cmd_env(char **cmd_tab_exec)
{
	t_lcl_var	*env_lst;
	t_lcl_var	*temp;

	env_lst = generate_envvar_list(NULL);
	temp = env_lst;
	while (temp)
	{
		if (ft_strlen(temp->name) > 1 || temp->name[0] != '?')
			printf("%s=%s\n", temp->name, temp->val);
		temp = temp->next;
	}
	(void)cmd_tab_exec;
	return (0);
}
