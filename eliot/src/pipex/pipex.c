/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/09/07 20:06:53 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int g_return_value;

int	pipex(char *cmd, char **env)
{
	t_pipex pipex;
	int		i;
	int		*id;
	//int		status;
	int		index_process;
	//int		pid;

	//premier split : division des pipes
	pipex.pipe_splited = ft_split(cmd, '|');
	pipex.nbr_of_pipe = how_many_pipe(pipex.pipe_splited);

	//creation du lexeur: mettre tout dans les stucts;
	if (lexeur_pipex(&pipex, cmd) == -1)
	{
		printf("error malloc\n");
		return (1);
	}

	// affiche sur le terminal les info du lexeur;
	//print_struc(pipex.lexeur);
	
	//parsing de pipex (verification de la syntax, ouverture des heres doc au fur et a mesure)
	paring_pipex(pipex.lexeur);

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
		pipex.return_value_var_global = manage_process(&pipex, index_process, env);
	}

	//attente des process dans le main
	if (id[i] != 0)
	{
	i = -1;
		while (++i < pipex.nbr_of_pipe)
		{
			int wstatus;
			int status;
			printf("child %d commence\n", id[i]);
			waitpid(id[i] , &wstatus, WUNTRACED);
			printf("child %d terminer\n", id[i]);
			if (WIFEXITED(wstatus))
				status = WEXITSTATUS(wstatus);
			else
				status = 128 + WTERMSIG(wstatus);
			printf("status :%d\n", status);
		}	
		i --;	
		//waitpid(id[i], NULL, );
		//wait(NULL);
		//write(2, "fin child\n", 10);
		close_all_fd(-1, -1, &pipex);
	}	
	del_list(&pipex);
	free_all_pipex(&pipex);
	if (id[i] == 0)
	{
		//write(2, "gosse qit\n", 10);
		exit(1);
	}
	//printf("pipex over\n");
	return (0);
}

int	manage_process(t_pipex *pipex, int index, char	**env)
{
	t_list_pipex	*tmp;
	int				fd_infile;
	int				fd_outfile;
	char			*full_path;
	//int				builtin;

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
		//printf("je me casse salut\n");
		close(fd_outfile);
		close(fd_infile);
		close(1);
		close(0);
		return (-2);
		//exit(1);
	}

	// test de la commande pour voir si c'est un absolute path
	// si == NULL alors je dois aller choper le path
	// sinon il y a deja le path et c'est niquel
	
	//cherche les builtins qu'on a coder pour les exec ici 
	/*builtin = cmd_type(pipex->cmd_tab_exec[0]);
	if (builtin) // si positif alors c'est un builtin
		do_builtins(builtin, pipex->cmd_tab_exec); // selon la valeur de builtin appelle la bonne fnction

*/	else 
	{
		pipex->cmd_with_path = testing_path(tmp);
		if (!pipex->cmd_with_path)
		{
			full_path = is_path_exist(pipex);
			if (full_path) // recherche du path: renvoi le path s'il existe
			{
				if (find_path(full_path, pipex) == 0) // recherche de la command dans le path renvoie 0 si trouve
				{
					/*printf("tu ne dois pas me voir\n");
					
					write(2, "\n", 1);
					write(2, "infile: ",8);
					write(2, ft_itoa(fd_infile), ft_strlen(ft_itoa(fd_infile)));
					write(2, "\n", 1);
					write(2, "outfile: ",9);
					write(2, ft_itoa(fd_outfile), ft_strlen(ft_itoa(fd_outfile)));
					write(2, "\n", 1);
					write(2, "\n", 1);
					if (index == pipex->nbr_of_pipe - 1)
					{
						char buff[1000];
						read(pipex->fd_pipe[index - 1][0], buff, 1000);
						write(2, buff, 1000);
					}*/
					write(2, "i did it\n", 9);
					execve(pipex->cmd_path, pipex->cmd_tab_exec, env);
				}
			}
		}
	}
	// a la fin de la fonction il faut close le fichier si erreur < ou de command	
	free_cmd_tab(pipex);
	close(fd_outfile);
	close(fd_infile);
	return (0);
}

int	how_many_pipe(char **cmd)
{
	int	i;	

	i = 0;
	while (cmd[i])
		i ++;
	return (i);
}
