/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/08 16:57:10 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

int	lexeur_pipex(t_pipex *pipex)
{
	int	i;

	//init lexeur 
	pipex->lexeur = init_struct_pipex();
	if (!pipex->lexeur)
	{
		del_list(pipex);
		return (-1);
	}

	// lecture de la cmd pour mettre dans la struct
	i = -1;
	while (pipex->cmd[++i]) // while pour chaque pipe
	{
		if (pipex->cmd[i] == '|')
			add_struct_pipex(pipex->lexeur, PIPE); // ajout d'un nouveau element pour un pipe
		// tchequer si le pipe commence par une commande
		if (pipex->cmd[i] || pipex->cmd[i] != '<' || pipex->cmd[i] != '>' || pipex->cmd[i] != '|')
		{
			add_struct_pipex(pipex->lexeur, CMD); // ajout d'un nouvelle element pour une command
			while (pipex->cmd[++i] || pipex->cmd[++i] != '<' || pipex->cmd[++i] != '>' || pipex->cmd[++i] != '|') 
				add_char_pipex(pipex->lexeur, pipex->cmd[i]); // ajout de char dans le nouvelle element
		}
		// agir selon le char surlequele on est
		if (pipex->cmd[i] && pipex->cmd[i] != '|' && pipex->cmd[i] == '<')
		{
			if (pipex->cmd[i + 1] != '<') // si on est sur <<
			{
				i + 2;
				while (pipex->cmd[i] == ' ') // tant qu'on a des espaces je skip
					i ++;
				while (pipex->cmd[i] && )
			}
			else // si on est sur <
		}
	}
	return (0);	
}
