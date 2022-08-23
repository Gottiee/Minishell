/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/08/23 20:01:08 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int g_return_value;

/*chose a faire: 
	- attention aux "" dans les here doc (ajouter au README)*/

int	pipex(char *cmd, char *path)
{
	t_pipex pipex;
	int		i;
	int		id;
	int		index_process;

	(void)path;

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
	print_struc(pipex.lexeur);
	
	//parsing de pipex (verification de la syntax, ouverture des heres doc au fur et a mesure)
	paring_pipex(pipex.lexeur);

	//creation du pipe ?
	//if (pipex.nbr_of_pipe > 1)
		pipe(pipex.fd_pipe);
	
	//creatio des processes
	id = 1;
	i = -1;
	while (++i < pipex.nbr_of_pipe)
	{
		if (id != 0)
		{
			index_process = i;
			id = fork();
		}
	}
	if (id == -1)
		return (-1);
	// fonction pour les process fork
	if (id == 0)
		pipex.return_value_var_global = manage_process(&pipex, index_process);

	//attente des process dans le main
	if (id != 0)
	{
		wait(0);
		close(pipex.fd_pipe[0]);
		close(pipex.fd_pipe[1]);
	}
	del_list(&pipex);
	free_all_pipex(&pipex);
	return (0);
}

/* chose a faire ! 

		- chercher env path (si path n'existe pas execve la command sans path) bash: ...: No such file or directory!! gerer le numero de retour
		- si path essayer de trouver la path,  si pas trouver: ...:command not found;
		- execve la command
		- faire des testes avec les fds open ect..
*/

int	manage_process(t_pipex *pipex, int index)
{
	t_list_pipex	*tmp;
	int				fd_infile;
	int				fd_outfile;

	// actual pipe te remvoie un pointeur sur le premier element du pipe que gere le fork
	tmp = actual_pipe(pipex->lexeur, index);
	// ouvre les < un par un et modifie dup la bonne sortie; 
	fd_infile = get_infile(tmp, index, pipex);
	if (fd_infile < 0)
		return (-1);

	// ouvre les  > et les >> chacun son tour et redirige 
	fd_outfile = get_outfile(tmp, index, pipex);
	if (fd_outfile < 0)		
		return (-1);

	//creation du tableau de tableau pour execve
	// la fonction return NULL si il n'y pas de commad dans le pipe
	pipex->cmd_tab_exec = creat_tab_exec(tmp, pipex);
	if (!pipex->cmd_tab_exec)
		return (-2);

	// test de la commande pour voir si c'est un absolute path
	// si == NULL alors je dois aller choper le path
	// sinon il y a deja le path et c'est niquel
	pipex->cmd_with_path = testing_path(tmp);
//	if (!pipex->cmd_with_path)
//		if (is_path_exist()) // recherche du path, savoir s'il existe
//			find_path(); // recherche de la command dans le path
	
	// execve

	// a la fin de la fonction il faut close le fichier si erreur < ou de command	
	free_cmd_tab(pipex);
	close(fd_outfile);
	close(fd_infile);
	close(0);
	close(1);
	close(2);
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
