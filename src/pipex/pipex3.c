/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:50:54 by eedy              #+#    #+#             */
/*   Updated: 2022/09/21 17:43:30 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	lexeur(char *cmd, t_pipex *pipex)
{
	pipex->pipe_splited = ft_split(cmd, '|');
	pipex->nbr_of_pipe = how_many_pipe(pipex->pipe_splited);
	if (lexeur_pipex(pipex, cmd) == -1)
	{
		printf("error malloc\n");
		return (-1);
	}
	return (0);
}

int	wait_child_do_cd(t_man3 *man, t_pipex *pipex)
{
	if (man->pid == 0)
	{
		close(man->fd[0]);
		close(man->fd[1]);
		del_list(pipex, man->pid);
		free_all_pipex(pipex);
		exit(1);
	}
	if (!WIFEXITED(man->wstatus))
	{
		ty_nor(man, pipex);
		return (man->status += (128 + WTERMSIG(man->wstatus)));
	}
	signal(SIGINT, &prompt_signal);
	man->cd_status = do_cd(pipex);
	del_list(pipex, man->pid);
	free_all_pipex(pipex);
	if (man->cd_status >= 0)
	{
		close(man->fd[0]);
		close(man->fd[1]);
		return (man->cd_status);
	}
	return (-80);
}

int	first_fork(t_man3 *man, char *cmd, t_pipex *pipex, char **env)
{
	man->status = 0;
	pipe(man->fd);
	if (lexeur(cmd, pipex) == -1)
		return (-1);
	man->pid = fork();
	if (man->pid == -1)
	{
		perror("bash: ");
		return (-1);
	}
	if (man->pid == 0)
	{
		close(man->fd[0]);
		signal(SIGINT, SIG_DFL);
		pipex2(env, man->fd, pipex);
	}
	else
	{
		close(man->fd[1]);
		signal(SIGINT, &signal_handle_fork);
		waitpid(man->pid, &man->wstatus, 0);
	}
	return (0);
}

void	wait_process(t_pipex *pipex, t_man2 *man)
{
	man->index_process = man->i;
	if (man->id[man->i] != 0)
	{
		signal(SIGINT, SIG_IGN);
		man->i = -1;
		close_all_fd(-1, -1, pipex);
		while (++man->i < pipex->nbr_of_pipe)
		{
			man->pid = waitpid(man->id[man->i], &man->wstatus, WUNTRACED);
			if (man->pid == man->id[man->index_process])
			{
				if (WIFEXITED(man->wstatus))
					man->status = WEXITSTATUS(man->wstatus);
				else
					man->status = 128 + WTERMSIG(man->wstatus);
			}
		}
		man->i--;
	}
}

int	creat_proccess(t_man2 *man, t_pipex *pipex, char **env)
{
	man->i = -1;
	man->id = malloc(sizeof(int) * pipex->nbr_of_pipe);
	while (++man->i < pipex->nbr_of_pipe)
	{
		man->index_process = man->i;
		man->id[man->i] = fork();
		if (man->id[man->i] == 0)
			break ;
	}
	if (man->i == pipex->nbr_of_pipe)
		man->i --;
	if (man->id[man->i] == -1)
		return (-1);
	if (man->id[man->i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		man->exit_status = manage_process(pipex, man->index_process, env);
	}
	return (0);
}
