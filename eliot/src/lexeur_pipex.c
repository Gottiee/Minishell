/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/09 18:48:45 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

int	lexeur_pipex(t_pipex *pipex, char *cmd)
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
	i = 0;
	pipe = 0;
	tchque_pipe = 0;
	printf("cmd = %s\n", cmd);
	while (cmd[i]) // while pour chaque pipe
	{
		if (cmd[i] == '|')
		{
			add_struct_pipex(pipex->lexeur, PIPE); // ajout d'un nouveau element pour un pipe
			add_char_pipex(pipex->lexeur, '|');
			tchque_pipe = pipe; // permet de savoir qu'on est rentre dans un pipe
			i ++;
		}
		// tchequer si le pipe commence par une commande
		if (tchque_pipe == pipe && (cmd[i] &&  (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && cmd[i] != ' ')))
		{
			// si le truc avant c'est un pipe j'ajoute un nouvel element 
			if (tchque_pipe == pipe)
			{
				add_struct_pipex(pipex->lexeur, CMD); // ajout d'un nouvel element pour une command
			}
			// sinon je continue la commande a joutant des espaces entre les options 
			else if (tchque_pipe == pipe)
				add_char_pipex(pipex->lexeur, ' ');
			while (cmd[i] && (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && cmd[i] != ' ')) 
			{
				add_char_pipex(pipex->lexeur, cmd[i]); // ajout de char dans le nouvelle element
				i ++;
			}
		}
		// traitement des << et des <
		if (cmd[i] && cmd[i] != '|' && cmd[i] == '<') 
		{
			if (cmd[i + 1] == '<') // si on est sur <<
			{
				i += 2;
				while (cmd[i] == ' ') // tant qu'on a des espaces je skip
					i ++;
				add_struct_pipex(pipex->lexeur, HERE_DOC); // creatin elem heredoc
				while (cmd[i] && (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && cmd[i] != ' ')) 
				{
					add_char_pipex(pipex->lexeur, cmd[i]);
					i ++;
				}
			}
			else // si on est sur <
			{
				i += 1;
 				// tant qu'on a des espaces je skip
				while (cmd[i] == ' ')
					i ++;
 				// creation elem infile
				add_struct_pipex(pipex->lexeur, INFILE);
				while (cmd[i] && (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && cmd[i] != ' ')) 
				{
					add_char_pipex(pipex->lexeur, cmd[i]);
					i ++;
				}
			}
		}
		// traitement des >> et des >
		else if (cmd[i] && cmd[i] != '|' && cmd[i] == '>') 
		{
			//si on est sur >>
			if (cmd[i + 1] == '>') 
			{
				i += 2;
				// skip d'espace
				while (cmd[i] == ' ')
					i ++;
				//creation d'dbl_outfile
				add_struct_pipex(pipex->lexeur, DBL_OUTFILE);
				while (cmd[i] && (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && cmd[i] != ' ')) 
				{
					add_char_pipex(pipex->lexeur, cmd[i]);
					i ++;
				}
			}
			else // si on est sur >
			{
				i += 1;
 				// tant qu'on a des espaces je skip
				while (cmd[i] == ' ')
					i ++;
 				// creation elem infile
				add_struct_pipex(pipex->lexeur, OUTFILE);
				while (cmd[i] && (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && cmd[i] != ' ')) 
				{
					add_char_pipex(pipex->lexeur, cmd[i]);
					i ++;
				}
			}
		}
		// traitment des option de la comande
		else if (cmd[i] && cmd[i] != '|' && cmd[i] != ' ')
		{
			while (cmd[i] == ' ')
				i ++;
			//add_char_pipex(pipex->lexeur, ' ');
			add_struct_pipex(pipex->lexeur, CMD);
			while (cmd[i] && (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && cmd[i] != ' ')) 
			{
				add_char_pipex(pipex->lexeur, cmd[i]); 
				i ++;
			}
		}
		pipe ++;
		while (cmd[i] == ' ')
			i ++;
	}
	return (0);	
}
