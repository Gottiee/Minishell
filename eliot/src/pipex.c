/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:22:17 by eedy              #+#    #+#             */
/*   Updated: 2022/08/05 13:12:44 by eedy             ###   ########.fr       */
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

	(void)path;

	//premier split : division des pipes
	pipex.pipe_splited = ft_split(cmd, '|');
	pipex.nbr_of_pipe = how_many_pipe(pipex.pipe_splited);

	//creation du pipe ?
	if (pipex.nbr_of_pipe > 1)
		pipe(pipex.fd_pipe);
	 
	//avant de fork il faut check la synatx

	if (parsing_error_syntax(cmd) == 1) // verifie que pas de << < > >> snas rien a la suite
	{
		// a la place de new line il faut mettre | si jamais on est dans un pipe
		printf("bash: syntax error near unexpected token `newline'\n");
		free_all_pipex(&pipex);
		return (1);
	}
		;
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
