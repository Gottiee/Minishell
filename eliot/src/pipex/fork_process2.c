/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:50:40 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 16:10:15 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	here_expension(int *count_infile, t_list_pipex *tmp, int id)
{
	if (*count_infile != 0)
		close(id);
	id = tmp->fd;
	dup2(tmp->fd, 0);
	(*count_infile)++;
}

int	infile_type2(int *count_infile, int id, t_list_pipex *tmp)
{
	char	*file_name;

	if (*count_infile != 0)
		close(id);
	file_name = concatenate_tstr(tmp->str_pipex);
	if (!file_name)
		return (-2);
	id = open(file_name, O_RDONLY, 0644);
	if (id == -1)
	{
		printf("-bash: %s: %s\n", file_name, strerror(errno));
		free(file_name);
		return (-1);
	}
	(*count_infile)++;
	free(file_name);
	return (id);
}

char	**cmd_tab_exec_length(int *cmd, t_list_pipex *tmp)
{
	char	**cmd_tab_exec;

	*cmd = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD)
			(*cmd)++;
		tmp = tmp->next;
	}
	if (*cmd == 0)
		return (NULL);
	cmd_tab_exec = malloc(sizeof(char *) * (*cmd + 1));
	if (!cmd_tab_exec)
		return (NULL);
	cmd_tab_exec[*cmd] = NULL;
	return (cmd_tab_exec);
}

int	while_find_path(int path_size, char **all_path, t_pipex *pipex, char *path)
{
	int	i;
	int	malloc_size;

	i = -1;
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
	return (-1);
}
