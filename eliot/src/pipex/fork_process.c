/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:16:05 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 15:22:33 by eedy             ###   ########.fr       */
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

/*creer un tableau de commande en partant de lexeur 
j'usque la fin de la lister chaine ou le prochain pipe*/
char	**creat_tab_exec(t_list_pipex *lexeur, t_pipex *pipex)
{
	t_list_pipex	*tmp;
	char			**cmd_tab_exec;
	int				cmd;
	int				i;

	tmp = lexeur;
	cmd_tab_exec = cmd_tab_exec_length(&cmd, tmp);
	if (!cmd_tab_exec)
		return (NULL);
	i = 0;
	tmp = lexeur;
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
	if (cpy[0] == '.')
		return (cmd);
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

int	find_path(char *full_path, t_pipex *pipex)
{
	char	**all_path;
	char	*path;
	int		path_size;

	path_size = 0;
	path = NULL;
	all_path = ft_split(full_path, ':');
	if (!all_path)
		return (-1);
	if (while_find_path(path_size, all_path, pipex, path) == 0)
		return (0);
	free_all_path(all_path);
	write(2, pipex->cmd_tab_exec[0], ft_strlen(pipex->cmd_tab_exec[0]));
	write(2, ": command not found\n", 20);
	return (-1);
}
