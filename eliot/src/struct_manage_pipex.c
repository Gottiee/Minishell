/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manage_pipex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:50:38 by eedy              #+#    #+#             */
/*   Updated: 2022/08/08 17:04:12 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

t_list_pipex	*init_struct_pipex(void)
{
	t_list_pipex	*new;
	
	new = malloc(sizeof(t_list_pipex));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->nbr_of_element = 0;
	return (new);
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
	new->str_pipex = NULL;
	return (0);
}

void	del_list_pipex(t_list_pipex *start)
{
	t_list_pipex	*tmp;

	free_tstr(start->str_pipex);
	while (start)
	{
		tmp = start;
		start = start->next;
		free(tmp);
	}
}

void	free_tstr(t_str *tstr)
{
	if (tstr->next)
		free_tstr(tstr->next);
	free(tstr);
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
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	new->c = char_p;
	return (0);
}
