/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/05 15:32:08 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

/*truc a faire pour demain: 
	- coder les fonctiosn pour les listes chainees (init, add, clear)
	- recuperer la fonction pour ajouter des char et la struc de theo
	- creer une foncion qui lit tout une fois et ajoute au fur et a mesure dans la lister chainee
	- <<her >test << non >> pk cat test < Makefile >"dan"s*/

int	parsing_fork(t_pipex *pipex) 
{
	// initialisation des list
	pipex->here_doc = init_struct_pipex();
	pipex->infile = init_struct_pipex();
	pipex->redirection = init_struct_pipex();
	pipex->dbl_redirection = init_struct_pipex();
	pipex->cmd_list = init_struct_pipex();
	if (!pipex->here_doc || !pipex->infile || !pipex->redirection || !pipex->dbl_redirection || !pipex->cmd_list)
	{
		del_list(pipex);
		return (-1);
	}
	//remplissage des listes:
	//detect_here_doc(pipex->here_doc, pipex);
	del_list(pipex); // creer la fonction qui appelle del_list pour chauque truc
	return (0);
}

/*int	detect_here_doc(t_list_pipex *here_doc, t_pipex *pipex)
{
	int	i;
	int	j;

	i = -1;
	while (pipex->cmd[++i])
	{
		if (pipex->cmd[i] == '<' || pipex->cmd[i + 1] == '<')
		{
			j = i + 2;	
		}
	}
	return (0);
}*/

char	parsing_error_syntax(char *cmd)
{
	int	i;
	int	j;
	char	value;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '<')
		{
			j = i + 1;
			while (cmd[j] == ' ')
				j ++;
			if (!cmd[j]|| cmd[j] == '>' || cmd[j] == '|')			
				return(return_value_parsing(j, cmd, 2));
		}
		value = parsing_error_syntax3(cmd, i ,j);
		if (value != 'q')
			return (value);
		value = parsing_error_syntax2(cmd, i, j);
		if (value != 'q')
			return (value);
	}
	return ('q');
}

char	parsing_error_syntax2(char *cmd, int i, int j)
{
	if (cmd[i] == '>')
	{
		j = i + 1;
		while (cmd[j] == ' ')
			j ++;
		if (!cmd[j] || cmd[j] == '<'|| cmd[j] == '|')			
			return (return_value_parsing(j, cmd, 0));
	}
	if (cmd[i] == '>')
	{
		if (cmd[i + 1] == '>')
		{
			j = i + 2;
			while (cmd[j] == ' ')
				j ++;
			if (!cmd[j] || cmd[j] == '<' || cmd[j] == '>' || cmd[j] == '|')			
				return(return_value_parsing(j, cmd, 1));
		}
	}
	return ('q');
}

char	parsing_error_syntax3(char *cmd, int i, int j)
{
	if (cmd[i] == '<')
	{
		if (cmd[i + 1] == '<')
		{
			j = i + 2;
			while (cmd[j] == ' ')
				j ++;
			if (!cmd[j] || cmd[j] == '<' || cmd[j] == '>' || cmd[j] == '|')			
				return (return_value_parsing(j, cmd, 1));
		}
	}
	return ('q');
}

char	return_value_parsing(int j, char *cmd, int bolo)
{
	if (!cmd[j])
		return ('n');
	if (cmd[j] == '|')
		return ('|');
	if (bolo != 2)
	{
		if (cmd[j] == '<')
			return ('<');
	}
	if (bolo != 0)
	{
		if (cmd[j] == '>')
			return ('>');
	}
	return ('q');
}
