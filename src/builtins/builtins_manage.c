/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:41:48 by eedy              #+#    #+#             */
/*   Updated: 2022/11/14 12:52:34 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	tilde_path(char **directory, char *buff, char *path)
{
	int	res;

	if (get_lclvar_by_name(generate_envvar_list(NULL), "HOME"))
	{
		if (path[1] == '\0')
		{
			free(path);
			return (move(directory, buff,
					ft_strdup(get_lclvar_by_name(generate_envvar_list(NULL)
							, "HOME")->val)));
		}
		res = move(directory, buff, ft_strjoin(ft_strdup(get_lclvar_by_name
						(generate_envvar_list(NULL), "HOME")->val),
					&(path[1])));
		free(path);
		return (res);
	}
	else
	{
		write(2, "bash: cd: HOME not set\n", 23);
		free_path_cd(buff, path);
		return (1);
	}
}

void	do_builtins(int builtin, char **cmd_tab_exec)
{
	if (builtin == CD)
		return ;
	if (builtin == ECHO)
		cmd_echo(cmd_tab_exec);
	if (builtin == EXPORT)
		return ;
	if (builtin == UNSET)
		return ;
	if (builtin == PWD)
		pwd();
	if (builtin == ENV)
		cmd_env(cmd_tab_exec);
}
