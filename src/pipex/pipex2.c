/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:05:55 by eedy              #+#    #+#             */
/*   Updated: 2022/10/21 14:02:18 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	lex_pipe(t_pipex *pipex, t_man2 *man, int fd[2])
{
	if (paring_pipex(pipex->lexeur) == -1)
	{
		man->status_char = ft_itoa(2);
		write(fd[1], man->status_char, ft_strlen(man->status_char));
		free(man->status_char);
		return (-1);
	}
	pipex->fd_pipe = NULL;
	if (pipex->nbr_of_pipe > 1)
	{
		pipex->fd_pipe = ft_calloc(pipex->nbr_of_pipe, sizeof(int *));
		if (!pipex->fd_pipe)
			return (-11);
		man->i = -1;
		while (++man->i < pipex->nbr_of_pipe - 1)
		{
			pipex->fd_pipe[man->i] = ft_calloc(2, sizeof(int));
			if (!pipex->fd_pipe[man->i])
				return (-1);
			if (pipe(pipex->fd_pipe[man->i]) < 0)
				return (-1);
		}
	}
	return (0);
}

int	free_man(t_manage *man, t_pipex *pipex)
{
	free_cmd_tab(pipex);
	close_all_fd(-1, -1, pipex);
	close(0);
	close(1);
	return (man->exec_status);
}

void	exec_file(t_pipex *pipex, char **env)
{
	int	i;

	i = -1;
	execve(pipex->cmd_with_path, pipex->cmd_tab_exec, env);
	while (++i < pipex->nbr_cmd)
		free(pipex->cmd_tab_exec[i]);
	free(pipex->cmd_tab_exec);
	pipex->cmd_tab_exec = malloc(sizeof(char *) * 3);
	pipex->cmd_tab_exec[0] = ft_strdup("bash");
	pipex->cmd_tab_exec[1] = pipex->cmd_with_path;
	pipex->cmd_tab_exec[2] = NULL;
	execve("/usr/bin/bash", pipex->cmd_tab_exec, env);
}

void	manage_process2(t_pipex *pipex, t_manage *man, char **env)
{
	pipex->cmd_with_path = testing_path(man->tmp);
	if (!pipex->cmd_with_path)
	{
		man->full_path = is_path_exist(pipex);
		if (man->full_path)
		{
			if (find_path(man->full_path, pipex) == 0)
			{
				execve(pipex->cmd_path, pipex->cmd_tab_exec, env);
				write(2, "'': command not found\n", 23);
				man->exec_status = 127;
			}
			else
				man->exec_status = 127;
		}
		else
			man->exec_status = 127;
	}
	else
	{
		if (check_executable(pipex->cmd_with_path))
			exec_file(pipex, env);
		else
			execve(pipex->cmd_with_path, pipex->cmd_tab_exec, env);
	}	
}

int	manage_process1(t_manage *man, int index, t_pipex *pipex)
{
	man->tmp = actual_pipe(pipex->lexeur, index);
	man->fd_infile = get_infile(man->tmp, index, pipex);
	if (man->fd_infile < 0)
		return (1);
	man->fd_outfile = get_outfile(man->tmp, index, pipex);
	if (man->fd_outfile < 0)
	{
		close(man->fd_infile);
		return (1);
	}
	close_all_fd(man->fd_outfile, man->fd_infile, pipex);
	pipex->cmd_tab_exec = creat_tab_exec(man->tmp, pipex);
	if (!pipex->cmd_tab_exec)
	{
		close(man->fd_outfile);
		close(man->fd_infile);
		close(1);
		close(0);
		return (0);
	}
	man->builtin = cmd_type(pipex->cmd_tab_exec[0]);
	return (3);
}
