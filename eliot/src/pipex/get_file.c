/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:00 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 16:12:21 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	get_infile(t_list_pipex *lexeur, int index, t_pipex *pipex)
{
	t_list_pipex	*tmp;
	int				id;
	int				id_tmp;

	id = 0;
	tmp = lexeur;
	if (pipex->nbr_of_pipe == 1)
		id_tmp = infile_type(tmp);
	else
	{
		if (index != 0)
		{
			dup2(pipex->fd_pipe[index - 1][0], 0);
			id = pipex->fd_pipe[index -1][0];
		}
		id_tmp = infile_type(tmp);
	}
	if (id_tmp != -1)
			id = id_tmp;
	return (id);
}

int	infile_type(t_list_pipex *tmp)
{
	int	id;	
	int	count_infile;

	id = -1;
	count_infile = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == HERE_DOC)
			here_expension(&count_infile, tmp, id);
		else if (tmp->type == INFILE)
		{
			id = infile_type2(&count_infile, id, tmp);
			if (id < 0)
				return (id);
		}
		tmp = tmp->next;
	}
	if (id != -1)
		dup2(id, 0);
	return (id);
}

int	get_outfile(t_list_pipex *lexeur, int index, t_pipex *pipex)
{
	t_list_pipex	*tmp;
	int				id;
	int				id_tmp;

	id = 1;
	tmp = lexeur;
	if (index == pipex->nbr_of_pipe -1)
		id_tmp = outfile_type(tmp);
	else
	{
		dup2(pipex->fd_pipe[index][1], 1);
		id = pipex->fd_pipe[index][1];
		id_tmp = outfile_type(tmp);
	}
	if (id_tmp != -1)
		id = id_tmp;
	return (id);
}

int	outfile_type2(int id, char *file_name, int *count_file, t_list_pipex *tmp)
{
	if (tmp->type == OUTFILE)
		id = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		id = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (id == -1)
	{
		write(2, "-bash: ", 7);
		write(2, file_name, ft_strlen(file_name));
		perror(":");
		free(file_name);
		return (-1);
	}
	(*count_file)++;
	free(file_name);
	return (id);
}

int	outfile_type(t_list_pipex *tmp)
{
	int		count_file;	
	int		id;
	char	*file_name;

	count_file = 0;
	id = -1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTFILE || tmp->type == DBL_OUTFILE)
		{
			if (count_file != 0)
				close(id);
			file_name = concatenate_tstr(tmp->str_pipex);
			if (!file_name)
				return (-2);
			id = outfile_type2(id, file_name, &count_file, tmp);
			if (id == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	if (id != -1)
		dup2(id, 1);
	return (id);
}
