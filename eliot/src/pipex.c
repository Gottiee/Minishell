/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/08/04 17:31:09 by eedy             ###   ########.fr       */
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
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	free_all_pipex(&pipex);
	printf("la valeur de retour de printf est = %d", pipex.return_value_var_global);
	return (pipex.return_value_var_global);
}

int	manage_process(t_pipex *pipex, int index)
{
	int	return_value_parsing;

	// stock dans cmd_splited toute la comande numero index, une nouvelle string par espace
	pipex->cmd_splited = ft_split(pipex->cmd_splited[index], ' ');
	pipex->cmd = pipex->cmd_splited[index];

	return_value_parsing = parsing_fork(pipex); // mets tout bines dans ma struct
	pipex->return_value_var_global = return_value;
	// differentes possibilite de return value

	if (return_value_parsing == 1) 
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (pipex->return_value_var_global);
	}
	
	//free la cmd splited stp
	free_in_fork(pipex); // a coder dans end and free
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
