/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:39:25 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/29 16:32:56 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"
//pourvoir export plusieurs choses
void	cmd_export(char **cmd)
{
	t_lcl_var	*var;
	t_lcl_var	*temp_env;
	t_lcl_var	*envvar;
	int			i;

	envvar = generate_envvar_list(NULL);
	i = 1;
	while (cmd[i])
	{
		if (is_var_cmd(cmd[i]) == 1)
		{
			var = create_lclvar(cmd[i]);
			temp_env = get_lclvar_by_name(&envvar, var->name);
			if (temp_env != NULL)
			{
				temp_env->val = ft_strdup(var->val);
				free_lclvar(var);
			}
			else
				add_back_lclvar(&envvar, var);
		}
		i++;
	}
	
}