/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:41:48 by eedy              #+#    #+#             */
/*   Updated: 2022/08/29 17:33:16 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	do_builtins(int builtin, char **cmd_tab_exec)
{
	if (builtin == CD)
		cd(cmd_tab_exec);
	if (builtin == ECHO)
		cmd_echo(cmd_tab_exec);
	if (builtin == EXPORT)
		cmd_export(cmd_tab_exec);
/*if (builtin == UNSET)
		cmd_unset(cmd_tab_exec);*/	
	if (builtin == PWD)
		pwd();
/*if (builtin == ENV)
		cmd_env(cmd_tab_exec);*/	
}
