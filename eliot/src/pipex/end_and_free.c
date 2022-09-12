/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:08:06 by eedy              #+#    #+#             */
/*   Updated: 2022/09/12 16:43:07 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	free_all_pipex(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->pipe_splited[++i])
		free(pipex->pipe_splited[i]);
	free(pipex->pipe_splited);
}

int	del_list(t_pipex *pipex)
{
	del_list_pipex(pipex->lexeur);
	return (-1);
}

void	free_cmd_tab(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nbr_cmd)
		free(pipex->cmd_tab_exec[i]);
	free(pipex->cmd_tab_exec);
	if (pipex->cmd_with_path)
		free(pipex->cmd_with_path);
}

void	free_all_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

void	close_all_fd(int fd_outfile, int fd_infile, t_pipex *pipex)
{
	int	i;
	
	i = 0;
	while (i < pipex->nbr_of_pipe - 1)
	{
		if (pipex->fd_pipe[i][0] != fd_infile && pipex->fd_pipe[i][0] != fd_outfile)
			close(pipex->fd_pipe[i][0]);
		if (pipex->fd_pipe[i][1] != fd_infile && pipex->fd_pipe[i][1] != fd_outfile)
			close(pipex->fd_pipe[i][1]);
		i++;
	}
}
