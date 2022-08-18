/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:16:05 by eedy              #+#    #+#             */
/*   Updated: 2022/08/18 14:04:01 by eedy             ###   ########.fr       */
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
		id = pipex->fd_pipe[0];
	}
	else
		close(pipex->fd_pipe[0]);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == HERE_DOC)
		{
			dup2(tmp->fd, 0);
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
			free(file_name);
		}
		tmp = tmp->next;
	}
	return (id);
}

int get_outfile(t_list_pipex *lexeur, int index, t_pipex *pipex)
{
	t_list_pipex	*tmp;
	int				fd;
	int				count_file;
	char			*file_name;
	int				fd_tmp;

	count_file = 0;
	fd_tmp = dup(STDOUT_FILENO);
	fd = 0;
	tmp = lexeur;
	if (index != pipex->nbr_of_pipe -1)
	{
		dup2(pipex->fd_pipe[1], 1);
		fd = pipex->fd_pipe[1];
	}
	else
		close(pipex->fd_pipe[1]);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTFILE || tmp->type == DBL_OUTFILE)
		{
			if (count_file != 0)
				close(fd);
			file_name = concatenate_tstr(tmp->str_pipex);
			if (!file_name)
				return (-2);
			if (tmp->type == OUTFILE)
				fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				dup2(fd_tmp, STDOUT_FILENO);	
				//dup2(fd_tmp, fd);
				printf("-bash: %s: %s\n", file_name, strerror(errno));
				return (-1);
			}
			dup2(fd, 1);
			count_file ++;
			free(file_name);
		}
		tmp = tmp->next;
	}
	return (fd);
}
