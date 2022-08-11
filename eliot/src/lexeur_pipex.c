/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/11 13:44:29 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

void	pipe_lexeur(t_pipex *pipex, char *cmd, int *i, t_pipe_lexeur lex)
{
	if (cmd[*i] == '|')
	{
		add_struct_pipex(pipex->lexeur, PIPE);
		add_char_pipex(pipex->lexeur, '|');
		*(lex.tchque_pipe) = *(lex.pipe);
		(*i)++;
	}
	if (*(lex.tchque_pipe) ==  *(lex.pipe)&& (cmd[*i] &&  (cmd[*i] != '<' && cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')))
	{
		// si le truc avant c'est un pipe j'ajoute un nouvel element 
		if (*(lex.tchque_pipe) == *(lex.pipe))
			add_struct_pipex(pipex->lexeur, CMD); // ajout d'un nouvel element pour une command
		else if (*(lex.tchque_pipe) == *(lex.pipe))
			add_char_pipex(pipex->lexeur, ' ');
		while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')) 
		{
			add_char_pipex(pipex->lexeur, cmd[*i]);
			(*i)++;
		}
	}
}

void	lexeur_front_chevron(t_pipex *pipex, char *cmd, int *i)
{
	if (cmd[*i] && cmd[*i] != '|' && cmd[*i] == '<') 
	{
		if (cmd[*i + 1] == '<') // si on est sur <<
		{
			(*i) += 2;
			while (cmd[*i] == ' ') // tant qu'on a des espaces je skip
				(*i) ++;
			add_struct_pipex(pipex->lexeur, HERE_DOC); // creatin elem heredoc
			while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')) 
			{
				add_char_pipex(pipex->lexeur, cmd[*i]);
				(*i) ++;
			}
		}
		else // si on est sur <
		{
			(*i) += 1;
 			// tant qu'on a des espaces je skip
			while (cmd[*i] == ' ')
				(*i) ++;
 			// creation elem infile
			add_struct_pipex(pipex->lexeur, INFILE);
			while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')) 
			{
				add_char_pipex(pipex->lexeur, cmd[*i]);
				(*i) ++;
			}
		}
	}
}

void	lexeur_back_chevron(t_pipex *pipex, char *cmd, int *i)
{
	if (cmd[*i] && cmd[*i] != '|' && cmd[*i] == '>') 
	{
		//si on est sur >>
		if (cmd[*i + 1] == '>') 
		{
			(*i) += 2;
			// skip d'espace
			while (cmd[*i] == ' ')
				(*i) ++;
			//creation d'dbl_outfile
			add_struct_pipex(pipex->lexeur, DBL_OUTFILE);
			while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')) 
			{
				add_char_pipex(pipex->lexeur, cmd[*i]);
				(*i) ++;
			}
		}
		else // si on est sur >
		{
			(*i) += 1;
 			// tant qu'on a des espaces je skip
			while (cmd[*i] == ' ')
				(*i) ++;
 			// creation elem infile
			add_struct_pipex(pipex->lexeur, OUTFILE);
			while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')) 
			{
				add_char_pipex(pipex->lexeur, cmd[*i]);
				(*i) ++;
			}
		}
	}
}


void	lexeur_cmd(t_pipex *pipex, char *cmd, int *i)
{
	if (cmd[*i] && cmd[*i] != '|' && cmd[*i] != ' ')
	{
		while (cmd[*i] == ' ')
			(*i) ++;
		//add_char_pipex(pipex->lexeur, ' ');
		add_struct_pipex(pipex->lexeur, CMD);
		while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')) 
		{
			add_char_pipex(pipex->lexeur, cmd[*i]); 
			(*i) ++;
		}
	}
}

int	lexeur_pipex(t_pipex *pipex, char *cmd)
{
	int				i;
	int				pipe;
	int				tchque_pipe;
	t_pipe_lexeur	lexeur;

	//init lexeur 
	pipex->lexeur = init_struct_pipex();
	if (!pipex->lexeur)
		return (del_list(pipex));
	lexeur.pipe = &pipe;
	lexeur.tchque_pipe = &tchque_pipe;
	
	// lecture de la cmd pour mettre dans la struct
	i = 0;
	pipe = 0;
	tchque_pipe = 0;
	printf("cmd = %s\n", cmd);
	while (cmd[i]) // while pour chaque pipe
	{
		// regarde si on est sur des pipes // et si oui, regarde si le mot d'apres est une commande
		pipe_lexeur(pipex, cmd, &i, lexeur);
		// traitement des << et des <
		lexeur_front_chevron(pipex, cmd, &i);
		// traitement des >> et des >
		lexeur_back_chevron(pipex, cmd, &i);
		// traitment des option de la comande
		lexeur_cmd(pipex, cmd, &i);
		pipe ++;
		while (cmd[i] == ' ')
			i ++;
	}
	return (0);	
}
