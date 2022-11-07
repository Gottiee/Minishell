/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:08:57 by eedy              #+#    #+#             */
/*   Updated: 2022/11/07 14:53:29 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	export_expend(t_pipex *pipex, t_cd *cd)
{
	if (cd->builtin == EXPORT)
		cd->cd_status = cmd_export(pipex->cmd_tab_exec);
	if (cd->builtin == UNSET)
		cd->cd_status = cmd_unset(pipex->cmd_tab_exec);
	if (cd->builtin == EXIT)
		cd->cd_status = cmd_exit(pipex->cmd_tab_exec, 0, pipex, NULL);
}

void	cd_expend(t_pipex *pipex, t_cd *cd, t_man3 *man)
{
	if (cd->index_process + 1 == pipex->nbr_of_pipe)
		cd->bolo = 1;
	cd->pid2 = fork();
	if (cd->pid2 == 0)
	{
		if (cd->builtin == CD)
			cd->cd_status = ft_cd(pipex->cmd_tab_exec);
		export_expend(pipex, cd);
		cd->i = -1;
		while (pipex->cmd_tab_exec[++cd->i])
			free(pipex->cmd_tab_exec[cd->i]);
		free(pipex->cmd_tab_exec);
		free_lclvar(generate_envvar_list(NULL));
		free(pipex->cmd);
		del_list(pipex, 0);
		close(man->fd[0]);
		exit(cd->cd_status);
	}
}

void	child_builtin(t_pipex *pipex, t_cd *cd, t_man3 *man)
{
	cd->index_process = -1;
	while (++cd->index_process < pipex->nbr_of_pipe)
	{
		cd->tmp = actual_pipe(pipex->lexeur, cd->index_process);
		pipex->cmd_tab_exec = creat_tab_exec(cd->tmp, pipex);
		if (!pipex->cmd_tab_exec)
			continue ;
		cd->builtin = cmd_type(pipex->cmd_tab_exec[0]);
		if (cd->builtin == CD || cd->builtin == EXPORT
			|| cd->builtin == UNSET || cd->builtin == EXIT)
		{
			cd_expend(pipex, cd, man);
			if (cd->pid2 != 0)
			{
				waitpid(-1, &cd->wstatus, 0);
				cd->cd_status = WEXITSTATUS(cd->wstatus);
			}
		}
		cd->i = -1;
		while (pipex->cmd_tab_exec[++cd->i])
			free(pipex->cmd_tab_exec[cd->i]);
		free(pipex->cmd_tab_exec);
	}
}

void	ty_nor(t_man3 *man, t_pipex *pipex)
{
	close(man->fd[0]);
	close(man->fd[1]);
	del_list(pipex, man->pid);
}
