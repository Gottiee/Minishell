/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:41:48 by eedy              #+#    #+#             */
/*   Updated: 2022/09/14 11:22:38 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	do_builtins(int builtin, char **cmd_tab_exec)
{
	if (builtin == CD)
		return ;
	/*cd(cmd_tab_exec);*/	
	if (builtin == ECHO)
		cmd_echo(cmd_tab_exec);
	if (builtin == EXPORT)
		cmd_export(cmd_tab_exec);
/*if (builtin == UNSET)
		cmd_unset(cmd_tab_exec);*/	
	if (builtin == PWD)
		pwd();
	if (builtin == ENV)
		cmd_env(cmd_tab_exec);	
}
