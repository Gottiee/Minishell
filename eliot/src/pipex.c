/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/08/16 17:08:51 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

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
	if (pipex.nbr_of_pipe > 1)
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
		wait(0);
	del_list(&pipex);
	free_all_pipex(&pipex);
	return (0);
}

int	manage_process(t_pipex *pipex, int index)
{
	/* chose a faire ! 

		- ecrire une fonction qui avance dans la liste chaine de x element jusqu'a arriver a son pipe on l'appeleraactual_pipe;
		- compris entre actual_pipe et la prochaine stuct '|' ou struct NULL definir et changer le stdin de notre pie (par defaut c'est 0 (entre standart)). ouvir les < 
		- compris entre ... changer et definir le stdout de notre fork: par defauti si rien c'est 1, si pipe apres c'est le pipe, sinon c'est les > et >> ouvert les uns apres les autres
		- creer le tableau de tableau pour execve et le remplir
		- tester la commande dans acess (pour check si c'est un absolute path);
		- chercher env path (si path n'existe pas execve la command sans path) bash: ...: No such file or directory!! gerer le numero de retour
		- si path essayer de trouver la path,  si pas trouver: ...:command not found;
	*/

}

int	how_many_pipe(char **cmd)
{
	int	i;	

	i = 0;
	while (cmd[i])
		i ++;
	return (i);
}
