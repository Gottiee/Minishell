/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:04:06 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:06:41 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

int	only_n(char *cmd)
{
	if (cmd)
	{
		if (*cmd == '\0')
			return (0);
		while (*cmd)
		{
			if (*cmd != 'n')
				return (0);
			cmd++;
		}
	}
	else
		return (0);
	return (1);
}

int	cmd_echo(char **cmd)
{
	int		n_option;
	int		i;
	int		prt;

	n_option = 0;
	i = 1;
	prt = 0;
	while (cmd[i] != NULL)
	{
		if (prt == 0 && cmd[i][0] == '-' && only_n(&(cmd[i][1])))
		{
			n_option = 1;
			i++;
			continue ;
		}
		prt = 1;
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
