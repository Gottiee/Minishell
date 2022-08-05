/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/08/05 16:49:29 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"
#include "../includes/minishell.h"

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

	//creation du pipe ?
	if (pipex.nbr_of_pipe > 1)
		pipe(pipex.fd_pipe);
	
	//avant de fork il faut check la synatx
	valeur = parsing_error_syntax(cmd);
	if (valeur != 'q') // verifie que pas de << < > >> snas rien a la suite
	{
		// si y'as un probleme et que pas de pipe ca va d'abord tester le here doc avant de dire que ca marche pas 
		// si y'as des pipes ca dit d'abord que ca marche pas avant de tester le here doc su premier pipe seulement
		if (pipex.nbr_of_pipe == 1)
		{
			printf("ici je vais executer un her doc pas encore coder\n");
			//exec_here_doc();
		}
		if (valeur == 'n')
			printf("bash: syntax error near unexpected token `newline'\n");
		else
			printf("bash: syntax error near unexpected token `%c'\n", valeur);
		if (pipex.nbr_of_pipe != 1)
			printf("ici je vais executer un her doc pas encore coder\n");
			//exec_here_doc();
		free_all_pipex(&pipex);
		return (1);
	}

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

	return_value_parsing = parsing_fork(pipex); // mets tout bines dans ma struct
	pipex->return_value_var_global = return_value;
	// differentes possibilite de return value

	
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
