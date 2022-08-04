/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:48:49 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/04 16:58:40 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

/*
Fonction qui retourne 1 si c'est une commande a executer avec execve 
	et 0 si c'est une commande qu'on doit coder nous meme
*/
/*
fix le pbm de echo "export"
*/
int	cmd_type(char *cmd)
{
	int	len_cmd;

	len_cmd = ft_strlen(cmd);
	if (ft_strnstr(cmd, "cd", len_cmd) != NULL)
		return (0);
	if (ft_strnstr(cmd, "pwd", len_cmd) != NULL)
		return (0);
	if (ft_strnstr(cmd, "export", len_cmd) != NULL)
		return (0);
	if (ft_strnstr(cmd, "unset", len_cmd) != NULL)
		return (0);
	if (ft_strnstr(cmd, "env", len_cmd) != NULL)
		return (0);
	if (ft_strnstr(cmd, "exit", len_cmd) != NULL)
		return (0);
	return (1);
}