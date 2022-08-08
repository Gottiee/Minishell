/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/08/08 14:24:00 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

int g_return_value;

/*chose a faire: 
-	faire le lexer qui met tout les arguments dans les structure: 
	-	mettre dans UNE structure tous les arguments les uns apres les autres commes ils sont appele
		- << < > >>
	-	 dans une struct a part metre les commandes
- 	lire dans l'ordre les instsrucition et verifier s'ils sont executables et que ca marche correctment 
	- faire les heres doc s'ils sont appele
	- attention aux "" dans les here doc (ajouter au README)
- ATTENTION: a partire de la return si error
- 	ouvrire les < 
-	ouvrire les >> et > suivant l'ordre de gauche a droite 
-	tester et exuter les commandes de gauche a droite
	- !! un pipe = fork donc si un rate les autres s'execute*/

int	pipex(char *cmd, char *path)
{
	t_pipex pipex;
	int		i;
	int		id;
	int		index_process;
	char	valeur;

	(void)path;

	//premier split : division des pipes
	pipex.pipe_splited = ft_split(cmd, '|');
	pipex.nbr_of_pipe = how_many_pipe(pipex.pipe_splited);

	//creation du lexeur: mettre tout dans les stucts;
	if (lexeur_pipex(&pipex) == -1)
	{
		printf("error malloc\n");
		return (1);
	}

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
	//gerer si fork fail

	// fonction pour les process fork
	if (id == 0)
		pipex.return_value_var_global = manage_process(&pipex, index_process);

	//attente des process dans le main
	if (id != 0)
		wait(0);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	del_list(&pipex);
	free_all_pipex(&pipex);
	return (0);
}

int	manage_process(t_pipex *pipex, int index)
{
	int	return_value_parsing;
	(void)return_value_parsing;

	// stock dans cmd_splited toute la comande numero index, une nouvelle string par espace
	pipex->cmd_splited = ft_split(pipex->pipe_splited[index], ' ');
	pipex->cmd = pipex->pipe_splited[index];
	
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
