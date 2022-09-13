/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/09/13 14:05:59 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	pipex(char *cmd, char **env)
{
	int		pid;
	int		fd[2];
	char	buffer[2];
	char	buff[4];
	int		i;
	
	pipe(fd);
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
		pipex2(cmd, env, fd);
	}
	else
	{
		close(fd[1]);
		signal(SIGINT, &signal_handle_fork);
		waitpid(pid, NULL, 0);
	}
	if (pid == 0)
		exit(1);
	signal(SIGINT, &prompt_signal);
	i = -1;
	while (read(fd[0], buffer, 1) > 0)
		buff[++i] = buffer[0];
	if (g_return_value == SIG)
		return (130);
	return (ft_atoi(buff));
	//return(0) ;
}

int	pipex2(char *cmd, char **env, int fd[2])
{
	t_pipex pipex;
	int		i;
	int		*id;
	int		index_process;
	int		wstatus;
	int		status;
	int		pid;
	char	*status_char;
	int		exit_status;

	//faire un premier fork qui va effectuer tout le parsing et toutes les commandes
	//premier split : division des pipes
	pipex.pipe_splited = ft_split(cmd, '|');
	pipex.nbr_of_pipe = how_many_pipe(pipex.pipe_splited);

	//creation du lexeur: mettre tout dans les stucts;
	if (lexeur_pipex(&pipex, cmd) == -1)
	{
		printf("error malloc\n");
		status_char = ft_itoa(2);
		write(fd[1], status_char, ft_strlen(status_char));
		free(status_char);
		return(-1);
	}

	// affiche sur le terminal les info du lexeur;
	//print_struc(pipex.lexeur);
	
	//parsing de pipex (verification de la syntax, ouverture des heres doc au fur et a mesure)
	if(paring_pipex(pipex.lexeur) == -1) 
	{
		status_char = ft_itoa(2);
		write(fd[1], status_char, ft_strlen(status_char));
		free(status_char);
		return(-1);
	}
	//creation du pipe ?
	//if (pipex.nbr_of_pipe > 1)
	
	// comptage nmb de pipe	
	pipex.fd_pipe = NULL;
	if (pipex.nbr_of_pipe > 1)
	{
		pipex.fd_pipe = ft_calloc(pipex.nbr_of_pipe, sizeof(int *));
		if (!pipex.fd_pipe)
			return (-11);
		i = -1;	
		while (++i < pipex.nbr_of_pipe - 1)
		{
			pipex.fd_pipe[i] = ft_calloc(2, sizeof(int));
			if (!pipex.fd_pipe[i])
				return (-1);
			if (pipe(pipex.fd_pipe[i]) < 0)
				return (-1);
		}
	}

	//creatio des processes
	i = -1;
	id = malloc(sizeof(int) * pipex.nbr_of_pipe);
	while (++i < pipex.nbr_of_pipe)
	{
		index_process = i;
		id[i] = fork();
		if (id[i] == 0)
			break;
		//printf("id enfant %d : %d\n", i, id[i]);
	}
	if (i == pipex.nbr_of_pipe)
		i --;
	if (id[i] == -1)
		return (-1);
	// fonction pour les process fork
	if (id[i] == 0)
	{
		// reset le signal ctrl-c a defaut c'est a dire kill the process
		signal(SIGINT, SIG_DFL);
		exit_status = manage_process(&pipex, index_process, env);
	}

	//attente des process dans le main
	index_process = i;
	if (id[i] != 0)
	{
		//signal(SIGINT, &signal_handle_fork);
		signal(SIGINT, SIG_IGN);
		i = -1;
		close_all_fd(-1, -1, &pipex);
		while (++i < pipex.nbr_of_pipe)
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
		

	// CD IN parent s'effectue apres le premier fork 
		int				builtin;
		t_list_pipex	*tmp;
		int				pid2;

	// si un seul pipe alors j'effectue cd
		if (pipex.nbr_of_pipe == 1)
		{
			pipex.cmd_tab_exec  = creat_tab_exec(pipex.lexeur, &pipex);
			if (!pipex.cmd_tab_exec)
				return(-1);
			builtin = cmd_type(pipex.cmd_tab_exec[0]);
			if (builtin == CD)
				cd(pipex.cmd_tab_exec);
			free(pipex.cmd_tab_exec);
		}
		//si pls pipe, je regarde si une des commandes a un cd, si oui je fork et je l'effectue dans un process tout seul
		else
		{
			index_process = -1;
			while (++index_process < pipex.nbr_of_pipe)
			{
				tmp = actual_pipe(pipex.lexeur, index_process);
				pipex.cmd_tab_exec = creat_tab_exec(tmp, &pipex);
				builtin = cmd_type(pipex.cmd_tab_exec[0]);
				if (builtin == CD)
				{
					pid2 = fork();
					if (pid2 == 0)
					{
						cd(pipex.cmd_tab_exec);
						free(pipex.cmd_tab_exec);
						exit(1);
					}
					else
						waitpid(-1, NULL, 0);
				}
				free(pipex.cmd_tab_exec);
			}
		}
	}

	//end and free
	del_list(&pipex);
	free_all_pipex(&pipex);
	if (id[i] == 0)
		exit(exit_status);
	//printf("status = %d\n", status);
	if (status == 1)
		status = 127;
	status_char = ft_itoa(status);
	write(fd[1], status_char, ft_strlen(status_char));
	//printf("status_char = %s\n", status_char);
	free(status_char);
	return (0);
}

int	manage_process(t_pipex *pipex, int index, char	**env)
{
	t_list_pipex	*tmp;
	int				fd_infile;
	int				fd_outfile;
	char			*full_path;
	int				builtin;
	int				exec_status;

	exec_status = 0;
	// actual pipe te remvoie un pointeur sur le premier element du pipe que gere le fork
	tmp = actual_pipe(pipex->lexeur, index);
	// ouvre les < un par un et modifie dup la bonne sortie; 
	fd_infile = get_infile(tmp, index, pipex);
	if (fd_infile < 0)
		return (-1);

	// ouvre les  > et les >> chacun son tour et redirige 
	fd_outfile = get_outfile(tmp, index, pipex);
	if (fd_outfile < 0)	
	{
		close(fd_infile);
		return (-1);
	}

	close_all_fd(fd_outfile, fd_infile, pipex);

	//creation du tableau de tableau pour execve
	// la fonction return NULL si il n'y pas de commad dans le pipe
	pipex->cmd_tab_exec = creat_tab_exec(tmp, pipex);
	if (!pipex->cmd_tab_exec)
	{
		close(fd_outfile);
		close(fd_infile);
		close(1);
		close(0);
		return (-2);
		//exit(1);
	}

	//cherche les builtins qu'on a coder pour les exec ici 
	builtin = cmd_type(pipex->cmd_tab_exec[0]);
	if (builtin) // si positif alors c'est un builtin
	{
		do_builtins(builtin, pipex->cmd_tab_exec); // selon la valeur de builtin appelle la bonne fnction
		pipex->cmd_with_path = NULL;
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
		}
		else
			execve(pipex->cmd_with_path, pipex->cmd_tab_exec, env);
	}
	// a la fin de la fonction il faut close le fichier si erreur < ou de command	
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
