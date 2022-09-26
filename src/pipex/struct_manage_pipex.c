/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manage_pipex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:50:38 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 14:44:09 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

t_list_pipex	*init_struct_pipex(void)
{
	t_list_pipex	*new;

	new = malloc(sizeof(t_list_pipex));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->str_pipex = NULL;
	new->type = -1;
	return (new);
}

void	add_bolo_here_doc(t_list_pipex *start)
{
	t_list_pipex	*tmp;	

	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	tmp->quote_here_doc = 1;
}

int	add_struct_pipex(t_list_pipex *start, int type)
{
	t_list_pipex	*new;
	t_list_pipex	*tmp;

	new = malloc(sizeof(t_list_pipex));
	if (!new)
		return (-1);
	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	new->type = type;
	new->file_name = NULL;
	new->quote_here_doc = 0;
	new->str_pipex = NULL;
	new->fd = -2;
	return (0);
}

void	del_list_pipex(t_list_pipex *start, int ok)
{
	t_list_pipex	*tmp;

	(void)ok;
	while (start)
	{
		tmp = start;
		start = start->next;
		if (tmp->type == 1)
		{
			if (tmp->file_name)
			{
				unlink(tmp->file_name);
				free(tmp->file_name);
			}
			if (tmp->fd != -2)
				close(tmp->fd);
		}
		free_tstr(tmp->str_pipex);
		free(tmp);
	}
}

int	add_char_pipex(t_list_pipex *start, char char_p)
{
	t_list_pipex	*tmp_p;
	t_str			*new;
	t_str			*tmp;

	new = malloc(sizeof(t_str));
	if (!new)
		return (-1);
	tmp_p = start;
	while (tmp_p ->next)
		tmp_p = tmp_p->next;
	tmp = tmp_p->str_pipex;
	if (!tmp)
	{
		tmp_p->str_pipex = new;
		new->next = NULL;
		new->c = char_p;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	new->c = char_p;
	return (0);
}
