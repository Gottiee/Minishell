/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:20:12 by eedy              #+#    #+#             */
/*   Updated: 2022/10/13 11:57:24 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	free_var_cmd_list(t_pipex *pipex)
{
	del_list(pipex, 0);
	close_all_fd(-1, -1, pipex);
	free(pipex->cmd);
	free_lclvar(generate_envvar_list(NULL));
}

void	free_stuf(t_pipex *pipex, t_man2 *man)
{
	free_var_cmd_list(pipex);
	free(man->id);
	free_fd_pipe(pipex);
}

void	free_fd_pipe(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->fd_pipe)
	{
		while (pipex->fd_pipe[++i])
			free(pipex->fd_pipe[i]);
		free(pipex->fd_pipe);
	}
}

int	expend_first(t_man3 *man)
{
	close(man->fd[1]);
	signal(SIGINT, &signal_handle_fork);
	waitpid(man->pid, &man->wstatus, 0);
	if (WEXITSTATUS(man->wstatus) == 2)
	{
		signal(SIGINT, &prompt_signal);
		return (-1);
	}
	return (0);
}
