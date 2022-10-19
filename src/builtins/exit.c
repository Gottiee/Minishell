/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:00:56 by eedy              #+#    #+#             */
/*   Updated: 2022/10/19 16:03:09 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	extend_exit(char **cmd, int *status)
{
	if (!cmd[1])
		*status = 0;
	else if (ft_atoi(cmd[1]) != -2147483646 && !cmd[2])
		*status = ft_atoi(cmd[1]);
	else if (ft_atoi(cmd[1]) != -2147483646 && cmd[2])
	{
		write(2, "bash: exit: too many arguments\n", 32);
		return (1);
	}
	else
	{
		write(2, "bash: exit: ", 12);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": numeric argument required\n", 29);
		*status = 2;
	}
	return (0);
}

int	cmd_exit(char **cmd, int bolo, t_pipex *pipex)
{
	int	status;	
	int	i;

	if (extend_exit(cmd, &status) == 1)
		return (1);
	if (bolo == 0)
		return (status);
	else
	{
		i = -1;
		while (pipex->cmd_tab_exec[++i])
			free(pipex->cmd_tab_exec[i]);
		free(pipex->cmd_tab_exec);
		free_var_cmd_list(pipex);
		write(2, "exit\n", 5);
		exit(status);
	}
}
