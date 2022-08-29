/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:04:06 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/29 15:45:24 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

//cmd : /bin/echo

//char **arg 
// arg[0]: echo

//pouvoir echo plusieurs str

void	cmd_echo(char *cmd, t_lcl_var **lclvar, t_lcl_var **envvar)
{
	int	n_option;
	
	while (*cmd == ' ')
		cmd++;
	cmd += 5;
	n_option = 0;
	if (ft_strnstr(cmd, "-n ", ft_strlen(cmd)) == cmd)
	{
		n_option = 1;
		cmd += 3;
	}
	printf("%s", get_txt(cmd, lclvar, envvar));
	if (n_option == 0)
		printf("\n");
}