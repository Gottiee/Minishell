/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manage_pipex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:50:38 by eedy              #+#    #+#             */
/*   Updated: 2022/08/23 16:08:37 by eedy             ###   ########.fr       */
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
	new->quote_here_doc = 0;
	new->str_pipex = NULL;
	return (0);
}

void	del_list_pipex(t_list_pipex *start)
{
	t_list_pipex	*tmp;

	while (start)
	{
		tmp = start;
		start = start->next;
		if (tmp->type == 1)
		{
			unlink(tmp->file_name);
			if (tmp->file_name)
				free(tmp->file_name);
			close(tmp->fd);
		}
		free_tstr(tmp->str_pipex);
		free(tmp);
	}
}

void	free_tstr(t_str *tstr)
{
	t_str	*tmp;

	tmp = tstr;
	while (tstr)
	{
		tmp = tstr;
		tstr = tstr->next;
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

int	add_char_here_doc(t_str *start, char char_p)
{
	t_str	*new;
	t_str	*tmp;

	tmp = start;
	if (!tmp->c)
	{
		tmp->c = char_p;
		tmp->next = NULL;
		return (0);
	}
	new = malloc(sizeof(t_str));
	if (!new)
		return (-1);
	
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	new->c = char_p;
	return (0);
}


char	*concatenate_tstr(t_str *node)
{
	t_str	*tmp;
	int		count_char;
	char	*str;
	int		i;

	i = -1;
	count_char = 0;
	tmp = node;
	while (tmp)
	{
		count_char ++;	
		tmp = tmp->next;
	}
	str = malloc(sizeof(char) * count_char + 1);
	if (!str)
		return (NULL);
	str[count_char] = '\0';
	tmp = node;
	while (++i < count_char)
	{
		str[i] = tmp->c;
		tmp = tmp->next;
	}
	return (str);
}

void	print_struc(t_list_pipex *start)
{
	t_list_pipex	*tmp;
	t_str			*tmp_str;

	tmp = start->next;

	while (tmp)
	{
		tmp_str = tmp->str_pipex;			
		printf("le numero de son type %d\n", tmp->type);
		if (tmp->type == 1)
			printf("valeur de bolo_quote %d\n", tmp->quote_here_doc);
		printf("chaine de cara enregistre :");
		while (tmp_str)
		{
			printf("%c",tmp_str->c);
			tmp_str = tmp_str->next;
		}
		printf("\n\n"); 
		tmp = tmp->next;
	}
}
