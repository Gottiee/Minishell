/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:18:07 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 17:30:21 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	lexeur(char *cmd, t_pipex *pipex)
{
	pipex->pipe_splited = ft_split(cmd, '|');
	pipex->nbr_of_pipe = how_many_pipe(pipex->pipe_splited);

	//creation du lexeur: mettre tout dans les stucts;
	if (lexeur_pipex(pipex, cmd) == -1)
	{
		printf("error malloc\n");
		return(-1);
	}
	return (0);
}

int	do_exp_uns(t_pipex *pipex)
{
	t_list_pipex	*tmp;
	int				index_process;
	int				builtin;
	int				bolo;
	int				status;
	int				cmd_status;
	int				i;

	status = -1;
	index_process = -1;
	bolo = 0;
	while (++index_process < pipex->nbr_of_pipe)
	{
		tmp = actual_pipe(pipex->lexeur, index_process);
		pipex->cmd_tab_exec = creat_tab_exec(tmp, pipex);
		builtin = cmd_type(pipex->cmd_tab_exec[0]);
		if (builtin == EXPORT || builtin == UNSET)
		{
			if (index_process + 1 == pipex->nbr_of_pipe)
				bolo = 1;
			if (builtin == EXPORT)
				cmd_status = cmd_export(pipex->cmd_tab_exec);
			if (builtin == UNSET)
				cmd_status = cmd_unset(pipex->cmd_tab_exec);
		}
		i = -1;
		while (pipex->cmd_tab_exec[++i])
				free(pipex->cmd_tab_exec[i]);
		free(pipex->cmd_tab_exec);
	}
	if (bolo == 1)
		status = cmd_status;
	return(status);
}

int	do_cd(t_pipex *pipex)
{
	t_list_pipex	*tmp;
	int				pid2;
	int				index_process;
	int				builtin;
	int				cd_status;
	int				bolo;
	int				wstatus;
	int				i;
	int				status;
	
	bolo = 0;
	cd_status = -1;
	if (pipex->nbr_of_pipe == 1)
	{
		pipex->cmd_tab_exec = creat_tab_exec(pipex->lexeur, pipex);
		if (!pipex->cmd_tab_exec)
			return(-2);
		builtin = cmd_type(pipex->cmd_tab_exec[0]);
		if (builtin == CD)
		{
			bolo = 1;
			cd_status = cd(pipex->cmd_tab_exec);
		}
		i = -1;
		while (pipex->cmd_tab_exec[++i])
				free(pipex->cmd_tab_exec[i]);
		free(pipex->cmd_tab_exec);
	}
		//si pls pipe, je regarde si une des commandes a un cd, si oui je fork et je l'effectue dans un process tout seul
	else
	{
		index_process = -1;
		while (++index_process < pipex->nbr_of_pipe)
		{
			tmp = actual_pipe(pipex->lexeur, index_process);
			pipex->cmd_tab_exec = creat_tab_exec(tmp, pipex);
			builtin = cmd_type(pipex->cmd_tab_exec[0]);
			if (builtin == CD)
			{
				if (index_process + 1 == pipex->nbr_of_pipe)
					bolo = 1;
				pid2 = fork();
				if (pid2 == 0)
				{
					cd_status = cd(pipex->cmd_tab_exec);
					free(pipex->cmd_tab_exec);
					exit(cd_status);
				}
				else
				{
					waitpid(-1, &wstatus, 0);
					cd_status = WEXITSTATUS(wstatus);
				}
			}
			i = -1;
			while (pipex->cmd_tab_exec[++i])
				free(pipex->cmd_tab_exec[i]);
			free(pipex->cmd_tab_exec);
		}
	}
	status = do_exp_uns(pipex);
	if (status >= 0)
		return(status);
	if (cd_status >= 0)
		return (cd_status);
	if (bolo == 1)
		return (cd_status);
	return (-1);
}

int	pipex(char *cmd, char **env)
{
	t_pipex	pipex;
	int		pid;
	int		fd[2];
	char	buffer[2];
	char	buff[4];
	int		i;
	int		cd_status;
	int		wstatus;
	int		status;
	
	status = 0;
	pipe(fd);
	if (lexeur(cmd, &pipex) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		perror("bash: ");
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, SIG_DFL);
		pipex2(env, fd, &pipex);
	}
	else
	{
		close(fd[1]);
		signal(SIGINT, &signal_handle_fork);
		waitpid(pid, &wstatus, 0);
	}
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		del_list(&pipex, pid);
		free_all_pipex(&pipex);
		exit(1);
	}
	if (!WIFEXITED(wstatus))
	{
		close(fd[0]);
		close(fd[1]);
		del_list(&pipex, pid);
		free_all_pipex(&pipex);
		return (status += (128 + WTERMSIG(wstatus)));
	}
	signal(SIGINT, &prompt_signal);
	cd_status = do_cd(&pipex);
	del_list(&pipex, pid);
	free_all_pipex(&pipex);
 	if (cd_status >= 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (cd_status);
	}
	i = -1;
	while (read(fd[0], buffer, 1) > 0)
		buff[++i] = buffer[0];
	buff[++i] = '\0'; 
	close(fd[0]);
	close(fd[1]);
	if (g_return_value == SIG)
		return (130);
	return (ft_atoi(buff));
	//return(0) ;
}

int	pipex2(char **env, int fd[2], t_pipex *pipex)
{
	int		i;
	int		*id;
	int		index_process;
	int		wstatus;
	int		status;
	int		pid;
	char	*status_char;
	int		exit_status;
	
	// affiche sur le terminal les info du lexeur;
	//print_struc(pipex.lexeur);
	
	//parsing de pipex (verification de la syntax, ouverture des heres doc au fur et a mesure)
	if(paring_pipex(pipex->lexeur) == -1) 
	{
		status_char = ft_itoa(2);
		write(fd[1], status_char, ft_strlen(status_char));
		free(status_char);
		return(-1);
	}
	//creation du pipe ?
	//if (pipex->nbr_of_pipe > 1)
	
	// comptage nmb de pipe	
	pipex->fd_pipe = NULL;
	if (pipex->nbr_of_pipe > 1)
	{
		pipex->fd_pipe = ft_calloc(pipex->nbr_of_pipe, sizeof(int *));
		if (!pipex->fd_pipe)
			return (-11);
		i = -1;	
		while (++i < pipex->nbr_of_pipe - 1)
		{
			pipex->fd_pipe[i] = ft_calloc(2, sizeof(int));
			if (!pipex->fd_pipe[i])
				return (-1);
			if (pipe(pipex->fd_pipe[i]) < 0)
				return (-1);
		}
	}

	//creatio des processes
	i = -1;
	id = malloc(sizeof(int) * pipex->nbr_of_pipe);
	while (++i < pipex->nbr_of_pipe)
	{
		index_process = i;
		id[i] = fork();
		if (id[i] == 0)
			break;
		//printf("id enfant %d : %d\n", i, id[i]);
	}
	if (i == pipex->nbr_of_pipe)
		i --;
	if (id[i] == -1)
		return (-1);
	// fonction pour les process fork
	if (id[i] == 0)
	{
		// reset le signal ctrl-c a defaut c'est a dire kill the process
		signal(SIGINT, SIG_DFL);
		exit_status = manage_process(pipex, index_process, env);
	}

	//attente des process dans le main
	index_process = i;
	if (id[i] != 0)
	{
		//signal(SIGINT, &signal_handle_fork);
		signal(SIGINT, SIG_IGN);
		i = -1;
		close_all_fd(-1, -1, pipex);
		while (++i < pipex->nbr_of_pipe)
		{
			pid = waitpid(id[i] , &wstatus, WUNTRACED);
			if (pid == id[index_process])
			{
				if (WIFEXITED(wstatus))
					status = WEXITSTATUS(wstatus);
				else
					status = 128 + WTERMSIG(wstatus);
			}
		}
		//signal(SIGINT, &prompt_signal);
		i --;	
	}

	//end and free
	//del_list(pipex);
	//free_all_pipex(pipex);
	if (id[i] == 0)
	{
		free_all_pipex(pipex);
		del_list(pipex, 0);
		close(fd[0]);
		close(fd[1]);
		exit(exit_status);
	}
	//printf("status = %d\n", status);
	if (status == 1)
		status = 127;
	status_char = ft_itoa(status);
	write(fd[1], status_char, ft_strlen(status_char));
	//printf("status_char = %s\n", status_char);
	free(status_char);
	free(id);
	return (0);
}

int	manage_process(t_pipex *pipex, int index, char	**env)
{
	t_manage	man;	
	int			return_status;

	man.exec_status = 0;
	return_status = manage_process1(&man, index, pipex);
	if (return_status < 1)
		return (return_status);


	// contiuer a partir d'ici a mmetre dans des foncitions et appele les variables dans la struc
	if (builtin && builtin != 99)
	{
		do_builtins(builtin, pipex->cmd_tab_exec);
		pipex->cmd_with_path = NULL;
	}
	else if (builtin == 99)
	{
		write(2, "bash: ", 6);
		write(2, pipex->cmd_tab_exec[0], ft_strlen(pipex->cmd_tab_exec[0]));
		write(2, ": wrong builtin call\n", 21);
		exec_status = 127;
	}
	else 
	{
		pipex->cmd_with_path = testing_path(tmp);
		if (!pipex->cmd_with_path)
		{
			full_path = is_path_exist(pipex);
			if (full_path) // recherche du path: renvoi le path s'il existe
			{
				if (find_path(full_path, pipex) == 0) // recherche de la command dans le path renvoie 0 si trouve
					execve(pipex->cmd_path, pipex->cmd_tab_exec, env);
				else
					exec_status = 127;
			}
			else
				exec_status = 127;
		}
		else
		{
			if (pipex->cmd_with_path[0] == '.')
			{
				i = -1;
				while (++i < pipex->nbr_cmd)
					free(pipex->cmd_tab_exec[i]);
				free(pipex->cmd_tab_exec);
				pipex->cmd_tab_exec = malloc(sizeof(char *) * 3);
				pipex->cmd_tab_exec[0] = ft_strdup("bash");
				pipex->cmd_tab_exec[1] = pipex->cmd_with_path;
				pipex->cmd_tab_exec[2] = NULL;
				execve("/usr/bin/bash", pipex->cmd_tab_exec, env);
			}
			else
				execve(pipex->cmd_with_path, pipex->cmd_tab_exec, env);
		}
	}
	free_cmd_tab(pipex);
	close(fd_outfile);
	close(fd_infile);
	close(0);
	close(1);
	return (exec_status);
}

int	how_many_pipe(char **cmd)
{
	int	i;	

	i = 0;
	while (cmd[i])
		i ++;
	return (i);
}
