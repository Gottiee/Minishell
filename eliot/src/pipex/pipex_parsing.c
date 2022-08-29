/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:56:37 by eedy              #+#    #+#             */
/*   Updated: 2022/08/23 16:08:31 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	paring_pipex(t_list_pipex *start)
{
	t_list_pipex	*tmp;

	tmp = start->next;
	while (tmp)	
	{
		// y'as un des < > >> puis rien d'ecrit apres
		if (tmp->type != PIPE && tmp->str_pipex == NULL)
		{
			// pas d'elem apres donc error newline
			if (tmp->next == NULL)
			{
				printf("-bash: syntax error near unexpected token `newline'\n");
				return (-1);
			}
			// ya un truc apres donc error l'elem d'apres
			else
			{
				tmp = tmp->next;
				return (print_error_syntax(tmp));
			}
		}
		if (parsing_pipex2(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	parsing_pipex2(t_list_pipex *tmp)
{
	// y 'as un |
	if (tmp->type == PIPE)
	{
		// pas d'elem apres donc error newline
		if (tmp->next == NULL)
		{
			printf("-bash: syntax error near unexpected token `newline'\n");
			return (-1);
		}
		// deux || colle donc error
		else if (tmp->next->type == PIPE)
		{
			printf("-bash: syntax error near unexpected token `|'\n");
			return (-1);
		}
	}
	// y 'as un << et que quelque chose est ecrit apres: tester le here doc
	if (tmp->type == HERE_DOC)
	{
		if (here_doc(tmp) == -1)
			return (-1);
	}
	return (0);
}

int	print_error_syntax(t_list_pipex *tmp)
{
	if (tmp->type == HERE_DOC)
		printf("-bash: syntax error near unexpected token `<<'\n");
	if (tmp->type == INFILE)
		printf("-bash: syntax error near unexpected token `<'\n");
	if (tmp->type == OUTFILE)
		printf("-bash: syntax error near unexpected token `>'\n");
	if (tmp->type == DBL_OUTFILE)
		printf("-bash: syntax error near unexpected token `>>'\n");
	if (tmp->type == PIPE)
		printf("-bash: syntax error near unexpected token `|'\n");
	return (-1);
}