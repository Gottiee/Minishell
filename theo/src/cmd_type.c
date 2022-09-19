/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:48:49 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/19 14:56:12 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

/*
Fonction qui retourne 1 si c'est une commande a executer avec execve 
	et 0 si c'est une commande qu'on doit coder nous meme
*/
int	builtin_val(char *cmd)
{
	int	len_cmd;

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

void	free_split(char **spl)
{
	int	i;

	i = 0;
	while (spl[i] != NULL)
	{
		free(spl[i]);
		i++;
	}
	free(spl);
}

int	cmd_type(char *cmd)
{
	char	**spl;
	int		i;
	char	*lst_wrd;

	if (cmd == NULL)
		return (-1);
	if (cmd[0] == '/')
	{
		spl = ft_split(cmd, '/');
		i = 0;
		while (spl[i] != NULL)
			i++;
		if (i == 0)
			return (0);
		lst_wrd = spl[i - 1];
		i = builtin_val(lst_wrd);
		free_split(spl);
		if (i > 0)
			return (99);
		return (0);
	}
	else
		return (builtin_val(cmd));
}
