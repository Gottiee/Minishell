/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_pipex2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:30:45 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 16:56:18 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	lexeur_front_chevron2(t_pipex *pipex, char *cmd, int *i)
{
	(*i) += 1;
	while (cmd[*i] == ' ')
		(*i)++;
	add_struct_pipex(pipex->lexeur, INFILE);
	while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>'
			&& cmd[*i] != '|' && cmd[*i] != ' '))
	{
		if (cmd[*i] == '"' || cmd[*i] == 39)
			quote_add_char(pipex, cmd, i, cmd[*i]);
		if (cmd[*i] != '"' && cmd[*i] != 39)
			add_char_pipex(pipex->lexeur, cmd[*i]);
		(*i)++;
	}
}

void	lexeur_back_chevron2(t_pipex *pipex, char *cmd, int *i)
{
	(*i) += 1;
	while (cmd[*i] == ' ')
		(*i)++;
	add_struct_pipex(pipex->lexeur, OUTFILE);
	while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>'
			&& cmd[*i] != '|' && cmd[*i] != ' '))
	{
		if (cmd[*i] == '"' || cmd[*i] == 39)
			if (quote_add_char(pipex, cmd, i, cmd[*i]) == 1)
				break ;
		if (cmd[*i] != '"' && cmd[*i] != 39)
			add_char_pipex(pipex->lexeur, cmd[*i]);
		(*i)++;
	}
}

void	lexeur_cmd(t_pipex *pipex, char *cmd, int *i)
{
	if (cmd[*i] && cmd[*i] != '|' && cmd[*i] != ' '
		&& cmd[*i] != '<' && cmd[*i] != '>')
	{
		while (cmd[*i] == ' ')
			(*i)++;
		add_struct_pipex(pipex->lexeur, CMD);
		while (cmd[*i] && (cmd[*i] != '<' && cmd[*i] != '>'
				&& cmd[*i] != '|' && cmd[*i] != ' '))
		{
			if (cmd[*i] == '"' || cmd[*i] == 39)
				if (quote_add_char(pipex, cmd, i, cmd[*i]) == 1)
					break ;
			if (cmd[*i] != '"' && cmd[*i] != 39)
				add_char_pipex(pipex->lexeur, cmd[*i]);
			(*i)++;
		}
	}
}

int	lexeur_pipex(t_pipex *pipex, char *cmd)
{
	int				i;
	int				pipe;
	int				tchque_pipe;
	t_pipe_lexeur	lexeur;

	pipex->lexeur = init_struct_pipex();
	if (!pipex->lexeur)
		return (del_list(pipex, 0));
	lexeur.pipe = &pipe;
	lexeur.tchque_pipe = &tchque_pipe;
	i = 0;
	pipe = 0;
	tchque_pipe = 0;
	while (cmd[i])
	{
		pipe_lexeur(pipex, cmd, &i, lexeur);
		lexeur_front_chevron(pipex, cmd, &i);
		lexeur_back_chevron(pipex, cmd, &i);
		lexeur_cmd(pipex, cmd, &i);
		pipe ++;
		while (cmd[i] == ' ')
			i ++;
	}
	return (0);
}
