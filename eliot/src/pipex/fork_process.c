/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:16:05 by eedy              #+#    #+#             */
/*   Updated: 2022/08/29 18:07:21 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

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
	int				bolo_pipe;

	count_infile = 0;
	id = 0;
	tmp = lexeur;
	bolo_pipe = 0;
	// si mon index n'est pas 0 ca veut dire qu'avant moi il y un pipe
	if (index != 0)
	{
		dup2(pipex->fd_pipe[0], 0);
		id = pipex->fd_pipe[0];
		bolo_pipe = 1;
	}
	else
		close(pipex->fd_pipe[0]);
	while (tmp && tmp->type != PIPE)
	{
		// je met en entre les here_doc
		if (tmp->type == HERE_DOC)
		{
			bolo_pipe = 0;
			dup2(tmp->fd, 0);
		}
		// je met en entre mon infile
		else if (tmp->type == INFILE)
		{
			bolo_pipe = 0;
			if (count_infile != 0)
				close(id);
			file_name = concatenate_tstr(tmp->str_pipex);
			if (!file_name)
				return (-2);
			id = open(file_name, O_RDONLY, 0644);
			// le fichier ne peux pas etre ouvert
			if (id == -1)
			{
				printf("-bash: %s: %s\n", file_name, strerror(errno));
				free(file_name);
				close(pipex->fd_pipe[1]);
				return (-1);
			}
			dup2(id, 0);
			count_infile ++;
			free(file_name);
		}
		tmp = tmp->next;
		if (!bolo_pipe)
			close(pipex->fd_pipe[0]);
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
	int				bolo_pipe;

	count_file = 0;
	fd_tmp = dup(STDOUT_FILENO);
	fd = 0;
	tmp = lexeur;
	bolo_pipe = 0;
	// je suis sur une comand qui a un pipe et je ne suis pas sur le dernier pipe
	if (pipex->nbr_of_pipe != 0 && index != pipex->nbr_of_pipe -1)
	{
		dup2(pipex->fd_pipe[1], 1);
		fd = pipex->fd_pipe[1];
		bolo_pipe = 1;
	}
	else
		close(pipex->fd_pipe[1]);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTFILE || tmp->type == DBL_OUTFILE)
		{
			bolo_pipe = 0;
			if (count_file != 0)
				close(fd);
			file_name = concatenate_tstr(tmp->str_pipex);
			if (!file_name)
				return (-2);
			if (tmp->type == OUTFILE)
				fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			//probleme pour ouvir le fichier; je ferme mes fichier et free, et remodifie le dup pour print sur la sorie standart
			if (fd == -1)
			{
				dup2(fd_tmp, STDOUT_FILENO);	
				//dup2(fd_tmp, fd);
				printf("-bash: %s: %s\n", file_name, strerror(errno));
				close(fd_tmp);
				free(file_name);
				close(pipex->fd_pipe[1]);
				return (-1);
			}
			dup2(fd, 1);
			count_file ++;
			free(file_name);
		}
		tmp = tmp->next;
	}
	if (!bolo_pipe)
		close(pipex->fd_pipe[1]);
	close(fd_tmp);
	return (fd);
}

char	**creat_tab_exec(t_list_pipex *lexeur, t_pipex *pipex)
{
	t_list_pipex	*tmp;
	char			**cmd_tab_exec;
	int				cmd;
	int				i;

	tmp = lexeur;
	cmd = 0;
	// je boucle une fois pour savoir la taille de *cmd_tab_exec
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD)	
			cmd ++;
		tmp = tmp->next;
	}
	tmp = lexeur;
	if (cmd == 0)
		return (NULL);
	cmd_tab_exec = malloc(sizeof(char *) * cmd);
	if (!cmd_tab_exec)
		return (NULL);

	// je met dans cmd_tab_exec les commandes les unes apres les autres
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD)
		{
			cmd_tab_exec[i] = concatenate_tstr(tmp->str_pipex);
			if (!cmd_tab_exec[i])
				return (NULL);
			i ++;
		}
		tmp = tmp->next;
	}
	pipex->nbr_cmd = cmd;
	return (cmd_tab_exec);
}

char	*testing_path(t_list_pipex *lexeur)
{
	t_list_pipex	*tmp;
	char			*cmd;
	char			*cpy;
	
	tmp = lexeur;
	while (tmp && tmp->type != PIPE && tmp->type != CMD)
		tmp = tmp->next;
	cmd = concatenate_tstr(tmp->str_pipex);
	cpy = cmd;
	if (access(cpy, X_OK) == 0)
		return (cmd);
	free(cmd);
	return (NULL);
}

char	*is_path_exist(t_pipex	*pipex)
{
	t_lcl_var	*envar;	
	t_lcl_var	*envpath;

	envar = generate_envvar_list(NULL);
	envpath = get_lclvar_by_name(&envar, "PATH");
	if (!envpath)
	{
		write(2, "bash: ", 6);
		write(2, pipex->cmd_tab_exec[0], ft_strlen(pipex->cmd_tab_exec[0]));
		write(2, ": No suche file or directory\n", 29);
		return (NULL);
	}
	return (envpath->val);
}

int find_path(char *full_path, t_pipex *pipex)
{
	char	**all_path;
	char	*path;
	int		i;
	int		malloc_size;
	int		path_size;

	i = -1;
	all_path = ft_split(full_path, ':');
	if (!all_path)
		return (-1);
	while (all_path[++i])
	{
		path_size = ft_strlen(all_path[i]);
		malloc_size = path_size + ft_strlen(pipex->cmd_tab_exec[0]);
		path = malloc(sizeof(char) * (malloc_size + 2));
		if (!path)
			return (-1);
		ft_strlcpy(path, all_path[i], path_size + 1);
		path[path_size] = '/';
		path[path_size + 1] = '\0';
		ft_strlcat(path, pipex->cmd_tab_exec[0], malloc_size + 2);
		if (access(path, X_OK) == 0)
		{
			free_all_path(all_path);
			pipex->cmd_path = path;
			return (0);
		}
		free(path);
	}
	free_all_path(all_path);
	write(2, pipex->cmd_tab_exec[0], ft_strlen(pipex->cmd_tab_exec[0]));
	write(2, ": command not found\n", 20);
	return (-1);
}
