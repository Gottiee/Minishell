/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:43:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/03 19:04:29 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

int	check_position_<(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (!pipex->cmd_splited[1])  // exemple: <
		{
			printf("-bash: syntax error near unexpected token `newline'\n");
			return (258);
		}
		else if (pipex->cmd_splited[1])  
		{
			if (pipex->cmd_splited[2]) // exemple: < file cmd
				return (1);
			else
				return (2); // exemple: < file
		}
	}
	else 
	{
		if (!pipex->cmd_splited[i + 1]) //exemple : cmd -option <
		{
			printf("-bash: syntax error near unexpected token `newline'\n");
			return (258);
		}
		else
			return(3);
					
	}
	return (0);
}
