/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:04:06 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/19 14:56:24 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

int	cmd_echo(char **cmd)
{
	int		n_option;
	int		i;

	n_option = 0;
	if (cmd[1] && ft_strnstr(cmd[1], "-n", ft_strlen(cmd[1])) == cmd[1])
		n_option = 1;
	i = 1 + n_option;
	while (cmd[i] != NULL)
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
