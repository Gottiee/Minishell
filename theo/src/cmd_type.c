/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:48:49 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/07 17:30:53 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

/*
Fonction qui retourne 1 si c'est une commande a executer avec execve 
	et 0 si c'est une commande qu'on doit coder nous meme
*/
int	cmd_type(char *cmd)
{
	int	len_cmd;
	if (cmd == NULL)
		return (-1);
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
