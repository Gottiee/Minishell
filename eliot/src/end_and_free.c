/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:08:06 by eedy              #+#    #+#             */
/*   Updated: 2022/08/11 10:51:28 by eedy             ###   ########.fr       */
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
