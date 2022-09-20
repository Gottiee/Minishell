/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:05:55 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 17:26:23 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int manage_process1(t_manage *man, int index, t_pipex *pipex)
{
	man->tmp = actual_pipe(pipex->lexeur, index);
	man->fd_infile = get_infile(man->tmp, index, pipex);
	if (man->fd_infile < 0)
		return (-1);
	man->fd_outfile = get_outfile(man->tmp, index, pipex);
	if (man->fd_outfile < 0)	
	{
		close(fd_infile);
		return (-1);
	}
	close_all_fd(man->fd_outfile, man->fd_infile, pipex);
	pipex->cmd_tab_exec = creat_tab_exec(man->tmp, pipex);
	if (!pipex->cmd_tab_exec)
	{
		close(man->fd_outfile);
		close(man->fd_infile);
		close(1);
		close(0);
		return (0);
	}
	man->builtin = cmd_type(pipex->cmd_tab_exec[0]);
	return (1);
}
