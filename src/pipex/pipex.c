/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:18:07 by eedy              #+#    #+#             */
/*   Updated: 2022/10/20 15:45:19 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

// int	do_exp_uns(t_pipex *pipex)
// {
// 	t_cd	cd;

// 	cd.status = -1;
// 	cd.index_process = -1;
// 	cd.bolo = 0;
// 	while (++cd.index_process < pipex->nbr_of_pipe)
// 	{
// 		cd.tmp = actual_pipe(pipex->lexeur, cd.index_process);
// 		pipex->cmd_tab_exec = creat_tab_exec(cd.tmp, pipex);
// 		cd.builtin = cmd_type(pipex->cmd_tab_exec[0]);
// 		if (cd.builtin == EXPORT || cd.builtin == UNSET)
// 			export_expend(pipex, &cd);
// 		cd.i = -1;
// 		while (pipex->cmd_tab_exec[++cd.i])
// 			free(pipex->cmd_tab_exec[cd.i]);
// 		free(pipex->cmd_tab_exec);
// 	}
// 	if (cd.bolo == 1)
// 		cd.status = cd.cmd_status;
// 	return (cd.status);
// }

int	do_cd(t_pipex *pipex, t_man3 *man)
{
	t_cd	cd;

	cd.bolo = 0;
	cd.cd_status = -1;
	if (pipex->nbr_of_pipe == 1)
	{
		if (parent_builtin(pipex, &cd, man) == -2)
			return (-2);
	}
	else
		child_builtin(pipex, &cd, man);
	if (cd.bolo == 1)
	{
		close(man->fd[0]);
		close(man->fd[1]);
		return (cd.cd_status);
	}
	return (-1);
}

int	pipex(char *cmd, char **env)
{
	t_man3	man;	
	t_pipex	pipex;
	int		return_status;
	int		i;

	pipex.cmd = cmd;
	if (first_fork(&man, cmd, &pipex, env) == -1)
		return (2);
	return_status = wait_child_do_cd(&man, &pipex);
	if (return_status != -80)
		return (return_status);
	i = -1;
	while (read(man.fd[0], man.buffer, 1) > 0)
		man.buff[++i] = man.buffer[0];
	man.buff[++i] = '\0';
	close(man.fd[0]);
	close(man.fd[1]);
	if (g_return_value == SIG)
		return (130);
	return (ft_atoi(man.buff));
}

int	pipex2(char **env, int fd[2], t_pipex *pipex)
{
	t_man2	man;	

	if (lex_pipe(pipex, &man, fd) < 0)
		return (-1);
	if (creat_proccess(&man, pipex, env) == -1)
		return (-1);
	wait_process(pipex, &man);
	if (man.id[man.i] == 0)
	{
		free_stuf(pipex, &man);
		close(fd[0]);
		close(fd[1]);
		exit(man.exit_status);
	}
	man.status_char = ft_itoa(man.status);
	write(fd[1], man.status_char, ft_strlen(man.status_char));
	free(man.status_char);
	close(fd[1]);
	close(fd[0]);
	free_stuf(pipex, &man);
	exit(0);
}

int	manage_process(t_pipex *pipex, int index, char	**env)
{
	t_manage	man;	
	int			return_status;

	man.exec_status = 0;
	return_status = manage_process1(&man, index, pipex);
	if (return_status < 3)
		return (return_status);
	if (man.builtin && man.builtin != 99)
	{
		do_builtins(man.builtin, pipex->cmd_tab_exec);
		pipex->cmd_with_path = NULL;
	}
	else if (man.builtin == 99)
	{
		write(2, "bash: ", 6);
		write(2, pipex->cmd_tab_exec[0], ft_strlen(pipex->cmd_tab_exec[0]));
		write(2, ": wrong builtin call\n", 21);
		man.exec_status = 127;
		pipex->cmd_with_path = NULL;
	}
	else
		manage_process2(pipex, &man, env);
	return (free_man(&man, pipex));
}
