/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/08 19:17:06 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

int	lexeur_pipex(t_pipex *pipex)
{
	int	i;
	int	pipe;
	int	tchque_pipe;

	//init lexeur 
	pipex->lexeur = init_struct_pipex();
	if (!pipex->lexeur)
	{
		del_list(pipex);
		return (-1);
	}

	// lecture de la cmd pour mettre dans la struct
	i = -1;
	pipe = 0;
	tchque_pipe = -1;
	while (pipex->cmd[++i]) // while pour chaque pipe
	{
		if (pipex->cmd[i] == '|')
		{
			add_struct_pipex(pipex->lexeur, PIPE); // ajout d'un nouveau element pour un pipe
			pipe++; // permet de savoir qu'on est rentre dans un pipe
		}
		// tchequer si le pipe commence par une commande
		if (pipex->cmd[i] || pipex->cmd[i] != '<' || pipex->cmd[i] != '>' || pipex->cmd[i] != '|')
		{
			// si le truc avant c'est un pipe j'ajoute un nouvel element 
			if (tchque_pipe != pipe)
			{
				pipe = tchque_pipe;
				add_struct_pipex(pipex->lexeur, CMD); // ajout d'un nouvel element pour une command
			}
			// sinon je continue la commande a joutant des espaces entre les options 
			else (tchque_pipe == pipe)
				add_char_pipex(pipex->lexeur, ' ');
			while (pipex->cmd[++i] || pipex->cmd[++i] != '<' || pipex->cmd[++i] != '>' || pipex->cmd[++i] != '|') 
				add_char_pipex(pipex->lexeur, pipex->cmd[i]); // ajout de char dans le nouvelle element
		}
		// traitement des << et des <
		if (pipex->cmd[i] && pipex->cmd[i] != '|' && pipex->cmd[i] == '<') 
		{
			if (pipex->cmd[i + 1] != '<') // si on est sur <<
			{
				i + 2;
				while (pipex->cmd[i] == ' ') // tant qu'on a des espaces je skip
					i ++;
				add_struct_pipex(pipex->lexeur, HERE_DOC); // creatin elem heredoc
				while (pipex->cmd[++i] && pipex->cmd[++i] != '|' && pipex->cmd[++i] != ' ')
					add_char_pipex(pipex->lexeur, pipex->cmd[i]);
			}
			else // si on est sur <
			{
				i + 1;
 				// tant qu'on a des espaces je skip
				while (pipex->cmd[i] == ' ')
					i ++;
 				// creation elem infile
				add_struct_pipex(pipex->lexeur, INFILE);
				while (pipex->cmd[++i] && pipex->cmd[++i] != '|' && pipex->cmd[++i] != ' ')
					add_char_pipex(pipex->lexeur, pipex->cmd[i]);
			}
		}
		// traitement des >> et des >
		else if (pipex->cmd[i] && pipex->cmd[i] != '|' && pipex->cmd[i] == '>') 
		{
			//si on est sur >>
			if (pipex->cmd[i + 1] != '>') 
			{
				i + 2;
				// skip d'espace
				while (pipex->cmd[i] == ' ')
					i ++;
				//creation d'dbl_outfile
				add_struct_pipex(pipex->lexeur, DBL_OUTFILE);
				while (pipex->cmd[++i] && pipex->cmd[++i] != '|' && pipex->cmd[++i] != ' ')
					add_char_pipex(pipex->lexeur, pipex->cmd[i]);
			}

		}
		// traitment des option des la comande
		
	}
	return (0);	
}
