/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:08:06 by eedy              #+#    #+#             */
/*   Updated: 2022/08/03 14:50:11 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"
#include "../includes/minishell.h"

void	free_all_pipex(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->pipe_splited[++i])
		free(pipex->pipe_splited[i]);
	free(pipex->pipe_splited);
}
