/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:16:05 by eedy              #+#    #+#             */
/*   Updated: 2022/08/17 17:45:12 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

t_list_pipex	*actual_pipe(t_list_pipex *lexeur, int index)
{
	t_list_pipex	*tmp;
	int				i;

	i = 0;
	tmp = lexeur;
	if (index == 0)
		return (tmp->next);
	tmp = tmp->next;
	while (i != index)
	{
		tmp = tmp->next;
		if (tmp->type == PIPE)
			i ++;
	}
	return (tmp->next);
}

int	get_infile(t_list_pipex *lexeur, int index, t_pipex *pipex)
{
	t_list_pipex	*tmp;
	int				id;
	int				count_infile;
	char			*file_name;

	count_infile = 0;
	id = 0;
	tmp = lexeur;
	if (index != 0)
	{
		dup2(pipex->fd_pipe[0], 0);
		printf("l'entre c'est le pipe d'avant\n");
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == HERE_DOC)
		{
			dup2(tmp->fd, 0);
			printf("Le fichier d'entrer est un here_doc\n");
		}
		else if (tmp->type == INFILE)
		{
			if (count_infile != 0)
				close(id);
			file_name = concatenate_tstr(tmp->str_pipex);
			if (!file_name)
				return (-2);
			id = open(file_name, O_RDONLY, 0644);
			if (id == -1)
			{
				printf("-bash: %s: %s\n", file_name, strerror(errno));
				return (-1);
			}
			dup2(id, 0);
			count_infile ++;
			printf("le fichier d'entrer est un inile nomme %s\n", file_name);
			free(file_name);
		}
		tmp = tmp->next;
	}
	return (id);
}
