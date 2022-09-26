/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:41:48 by eedy              #+#    #+#             */
/*   Updated: 2022/09/19 14:59:03 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

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
