/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:04:06 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/29 16:18:48 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

void	cmd_echo(char **cmd)
{
	int		n_option;
	int		i;
	char	*txt;

	n_option = 0;
	if (ft_strnstr(cmd[1], "-n", ft_strlen(cmd[1])) == cmd[1])
		n_option = 1;
	i = 1 + n_option;
	while (cmd[i] != NULL)
	{
		txt = get_txt(cmd[i]);
		write(1, txt, ft_strlen(txt));
		free(txt);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
}