/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/10/20 15:55:39 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	quote_add_char_here(t_pipex *pipex, char *cmd, int *i, int quote)
{
	if (cmd[*i + 1] == quote && (cmd[*i + 2] == ' ' || cmd[*i + 2] == '\0'))
	{
		if (*i == 0 || (cmd[*i -1] == ' ' || cmd[*i -1] == '|'
				|| cmd[*i -1] == '>' || cmd[*i -1] == '<'))
		{
			add_char_pipex(pipex->lexeur, '\n');
			*i += 2;
			return (1);
		}
	}
	*i += 1;
	while (cmd[*i] != quote)
	{
		add_char_pipex(pipex->lexeur, cmd[*i]);
		(*i)++;
	}
	return (0);
}

void	pipe_lexeur(t_pipex *pipex, char *cmd, int *i, t_pipe_lexeur lex)
{
	if (cmd[*i] == '|')
	{
		add_struct_pipex(pipex->lexeur, PIPE);
		add_char_pipex(pipex->lexeur, '|');
		*(lex.tchque_pipe) = *(lex.pipe);
		(*i)++;
	}
	if (*(lex.tchque_pipe) == *(lex.pipe) && (cmd[*i] && (cmd[*i] != '<'
				&& cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' ')))
	{
		if (*(lex.tchque_pipe) == *(lex.pipe))
			add_struct_pipex(pipex->lexeur, CMD);
		else if (*(lex.tchque_pipe) == *(lex.pipe))
			add_char_pipex(pipex->lexeur, ' ');
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

int	quote_add_char(t_pipex *pipex, char *cmd, int *i, int quote)
{
	if (cmd[*i + 1] == quote && (cmd[*i + 2] == ' ' || cmd[*i + 2] == '\0'))
	{
		if (*i == 0 || (cmd[*i -1] == ' ' || cmd[*i -1] == '|'
				|| cmd[*i -1] == '>' || cmd[*i -1] == '<'))
		{
			add_char_pipex(pipex->lexeur, '\0');
			*i += 2;
			return (1);
		}
	}
	*i += 1;
	while (cmd[*i] != quote)
	{
		add_char_pipex(pipex->lexeur, cmd[*i]);
		(*i)++;
	}
	return (0);
}

void	lexeur_front_chevron(t_pipex *pipex, char *cmd, int *i)
{
	if (cmd[*i] && cmd[*i] != '|' && cmd[*i] == '<')
	{
		if (cmd[*i + 1] == '<')
		{
			(*i) += 2;
			while (cmd[*i] == ' ')
				(*i)++;
			add_struct_pipex(pipex->lexeur, HERE_DOC);
			while (cmd[*i] && (cmd[*i] != '<'
					&& cmd[*i] != '>' && cmd[*i] != '|' && cmd[*i] != ' '))
			{
				if (cmd[*i] == '"' || cmd[*i] == 39)
				{
					if (quote_add_char_here(pipex, cmd, i, cmd[*i]) == 1)
						break ;
					add_bolo_here_doc(pipex->lexeur);
				}
				if (cmd[*i] != '"' && cmd[*i] != 39)
					add_char_pipex(pipex->lexeur, cmd[*i]);
				(*i)++;
			}
		}
		else
			lexeur_front_chevron2(pipex, cmd, i);
	}
}

void	lexeur_back_chevron(t_pipex *pipex, char *cmd, int *i)
{
	if (cmd[*i] && cmd[*i] != '|' && cmd[*i] == '>')
	{
		if (cmd[*i + 1] == '>')
		{
			(*i) += 2;
			while (cmd[*i] == ' ')
				(*i)++;
			add_struct_pipex(pipex->lexeur, DBL_OUTFILE);
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
		else
			lexeur_back_chevron2(pipex, cmd, i);
	}
}
