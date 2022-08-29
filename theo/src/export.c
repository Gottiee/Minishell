/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:39:25 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/29 15:45:03 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"
//pourvoir export plusieurs choses
void	cmd_export(char *cmd, t_lcl_var **lclvar, t_lcl_var **envvar)
{
	t_lcl_var	*var;
	t_lcl_var	*temp_env;

	while (*cmd == ' ')
		cmd++;
	cmd += 7;
	if (is_var_cmd(cmd) == 1)
	{
		var = create_lclvar(cmd, lclvar, envvar);
		temp_env = get_lclvar_by_name(envvar, var->name);
		if (temp_env != NULL)
		{
			temp_env->val = ft_strdup(var->val);
			free_lclvar(var);
		}
		else
			add_back_lclvar(envvar, var);
	}
}