/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/08/03 17:49:30 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

int	pipex(char *cmd, char *path)
{
	t_pipex pipex;
	int		i;
	int		id;
	int		index_process;

	//premier split : division des pipes
	pipex.pipe_splited = ft_split(cmd, '|');
	pipex.nbr_of_pipe = how_many_pipe(pipex.pipe_splited);

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
	free_all_pipex(&pipex);
	printf("la valeur de retour de printf est = %d", pipex.return_value_var_global);
	return (pipex.return_value_var_global);
}

int	manage_process(t_pipex *pipex, int index)
{
	int	return_value;
	// stock dans cmd_splited toute la comande numero index, une nouvelle string par espace
	pipex->cmd_splited = split(pipex->cmd_splited[index], ' ');

	// verifie les << < > >>
	return_value = parsing_fork(pipex);

	// differentes possibilite de return value
	
	if (return_value == 0) //pas trouver de truc
	if (return_value == 258) // < & << syntax error
		return (258);
	if (return_value == 1) // < && << infile plus cmd : < file cmd -option....
		return (infile_plus_cmd(pipex)); // return pas si execve ou autre pour les problems: si execve modifier la valeur de la var global avant d'exec
	if (return_valuee == 2) // < && << infile: < file
		return (infile(pipex)); //return (0) si reussi a ouvrire le fichier et 1 si pas trouver le fichier
	if (return_value == 3) // < && << infile + cmd : cmd -option.. < file -option...
		return (infile_plus_cmd_reverse(pipex)); // return pas si execve ou autre pour les problems: si execve modifier la valeur de la var global avant d'exec

	return (0);
}

int	parsing_fork(t_pipex *pipex)
{
	int	i;

	// check < first
	i = -1;
	while (pipex->cmd_splited[++i])
	{
		if (pipex->cmd_splited[i][0] == '<')
			if (!pipex->cmd_splited[i][1])
				return (check_postion_<(pipex, i));
	}
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
