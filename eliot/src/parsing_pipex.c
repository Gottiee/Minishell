/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/08 14:29:54 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

int	lexeur_pipex(t_pipex *pipex)
{
	int	i;

	//init lexeur + cmd
	pipex->lexeur = init_struct_pipex();
	pipex->cmd_list = init_struct_pipex();
	if (!pipex->lexeur || !pipex->cmd_list)
	{
		del_list(pipex);
		return (-1);
	}

	// lecture de la cmd pour mettre dans la struct
	i = -1;
	while (pipex->cmd[++i])
	{
		while (pipex->cmd[i] != '<' || pipex->cmd[i] != '>' || pipex->cmd[i] != '|') // je tchque si je commance par une commande
		{
			add_struct_pipex(pipex->cmd_list); // ajout d'un new list pour cmd
			add_char_pipex(pipex->cmd_list->str_pipex, pipex->cmd[i]); // ajout de char dans la nouvelle list
			i ++;	
		}
	}
	return (0);	
}
