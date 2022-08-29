/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:48:49 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/27 20:19:59 by tokerman         ###   ########.fr       */
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

	while (*cmd && *cmd == ' ')
		cmd++;
	len_cmd = ft_strlen(cmd);
	if (ft_strnstr(cmd, "cd", len_cmd) == cmd)
		return (-1);
	if (ft_strnstr(cmd, "pwd", len_cmd) == cmd)
		return (-2);
	if (ft_strnstr(cmd, "export", len_cmd) == cmd)
		return (-3);
	if (ft_strnstr(cmd, "unset", len_cmd) == cmd)
		return (-4);
	if (ft_strnstr(cmd, "env", len_cmd) == cmd)
		return (-5);
	if (ft_strnstr(cmd, "exit", len_cmd) == cmd)
		return (-6);
	if (ft_strnstr(cmd, "echo", len_cmd) == cmd)
		return (-7);
	return (1);
}