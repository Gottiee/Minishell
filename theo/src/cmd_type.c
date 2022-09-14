/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:48:49 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/14 16:40:20 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

/*
Fonction qui retourne 1 si c'est une commande a executer avec execve 
	et 0 si c'est une commande qu'on doit coder nous meme
*/

//bin/echo


int	cmd_type(char *cmd)
{
	int	len_cmd;
	if (cmd == NULL)
		return (-1);
	// split de la commande a chaque "/" 
	// si cmd[1] == '/' && last split == a un builtin
	// alors retrurn (10); !! gerer pour ne pas l'executer apres ! 
	len_cmd = ft_strlen(cmd);
	if (ft_strnstr(cmd, "cd", len_cmd) == cmd)
		return (CD);
	if (ft_strnstr(cmd, "pwd", len_cmd) == cmd)
		return (PWD);
	if (ft_strnstr(cmd, "export", len_cmd) == cmd)
		return (EXPORT);
	if (ft_strnstr(cmd, "unset", len_cmd) == cmd)
		return (UNSET);
	if (ft_strnstr(cmd, "env", len_cmd) == cmd)
		return (ENV);
	if (ft_strnstr(cmd, "exit", len_cmd) == cmd)
		return (EXIT);
	if (ft_strnstr(cmd, "echo", len_cmd) == cmd)
		return (ECHO);
	return (0);
}
