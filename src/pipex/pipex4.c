/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:08:57 by eedy              #+#    #+#             */
/*   Updated: 2022/09/21 17:39:15 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	export_expend(t_pipex *pipex, t_cd *cd)
{
	if (cd->index_process + 1 == pipex->nbr_of_pipe)
		cd->bolo = 1;
	if (cd->builtin == EXPORT)
		cd->cmd_status = cmd_export(pipex->cmd_tab_exec);
	if (cd->builtin == UNSET)
		cd->cmd_status = cmd_unset(pipex->cmd_tab_exec);
}

void	cd_expend(t_pipex *pipex, t_cd *cd)
{
	if (cd->index_process + 1 == pipex->nbr_of_pipe)
		cd->bolo = 1;
	cd->pid2 = fork();
	if (cd->pid2 == 0)
	{
		cd->cd_status = ft_cd(pipex->cmd_tab_exec);
		free(pipex->cmd_tab_exec);
		//
		free_lclvar(generate_envvar_list(NULL));
		free(pipex->cmd);
		del_list(pipex, 0);
		close_all_fd(-1, -1, pipex);
		//
		exit(cd->cd_status);
	}
}

void	cd2(t_pipex *pipex, t_cd *cd)
{
	cd->index_process = -1;
	while (++cd->index_process < pipex->nbr_of_pipe)
	{
		cd->tmp = actual_pipe(pipex->lexeur, cd->index_process);
		pipex->cmd_tab_exec = creat_tab_exec(cd->tmp, pipex);
		cd->builtin = cmd_type(pipex->cmd_tab_exec[0]);
		if (cd->builtin == CD)
		{
			cd_expend(pipex, cd);
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

int	cd1(t_pipex *pipex, t_cd *cd)
{
	pipex->cmd_tab_exec = creat_tab_exec(pipex->lexeur, pipex);
	if (!pipex->cmd_tab_exec)
		return (-2);
	cd->builtin = cmd_type(pipex->cmd_tab_exec[0]);
	if (cd->builtin == CD)
	{
		cd->bolo = 1;
		cd->cd_status = ft_cd(pipex->cmd_tab_exec);
	}
	cd->i = -1;
	while (pipex->cmd_tab_exec[++cd->i])
		free(pipex->cmd_tab_exec[cd->i]);
	free(pipex->cmd_tab_exec);
	return (0);
}

void	ty_nor(t_man3 *man, t_pipex *pipex)
{
	close(man->fd[0]);
	close(man->fd[1]);
	del_list(pipex, man->pid);
	// free_all_pipex(pipex);
}
