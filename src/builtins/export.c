/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:39:25 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:06:52 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

int	check_isalnum(char *name, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			free(name);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	correct_syntax(char *cmd)
{
	t_str	*name_tstr;
	int		size;
	char	*name;

	name_tstr = NULL;
	while (*cmd && *cmd != '=')
		add_back_tstr(&name_tstr, create_tstr(*cmd++));
	if (!*cmd)
	{
		free_tstr(name_tstr);
		return (0);
	}
	cmd++;
	name = get_str_with_tstr(name_tstr);
	size = ft_strlen(name);
	if ((size == 1 && name[0] == '_') || get_type_val(name) == 0)
	{
		free(name);
		return (-1);
	}
	if (check_isalnum(name, size) == -1)
		return (-1);
	free(name);
	return (1);
}

/*
export =ters
bash: export: `': not a valid identifier
*/
int	err_export(char *cmd)
{
	t_str	*name_tstr;
	char	*name;

	if (cmd[0] == '=')
	{
		printf("bash: export: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	name_tstr = NULL;
	while (*cmd && *cmd != '=')
		add_back_tstr(&name_tstr, create_tstr(*cmd++));
	name = get_str_with_tstr(name_tstr);
	printf("bash: export: `%s': not a valid identifier\n", name);
	free(name);
	return (1);
}

void	update_var_val(t_lcl_var *dst, t_lcl_var *src)
{
	free(dst->val);
	dst->val = ft_strdup(src->val);
	free_lclvar(src);
}

int	cmd_export(char **cmd)
{
	t_lcl_var	*var;
	t_lcl_var	*temp_env;
	t_lcl_var	*envvar;
	int			i;

	envvar = generate_envvar_list(NULL);
	i = 1;
	while (cmd[i])
	{
		if (correct_syntax(cmd[i]) == 1)
		{
			var = create_lclvar(cmd[i]);
			temp_env = get_lclvar_by_name(envvar, var->name);
			if (temp_env != NULL)
				update_var_val(temp_env, var);
			else
				add_back_lclvar(&envvar, var);
		}
		else if (correct_syntax(cmd[i]) == -1)
			return (err_export(cmd[i]));
		i++;
	}
	return (0);
}
