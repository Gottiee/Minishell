/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:08:06 by eedy              #+#    #+#             */
/*   Updated: 2022/08/18 16:50:10 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

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
}
