/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:39:36 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/09 17:45:02 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

void	add_back_histcmd(t_hist_cmd **first, t_hist_cmd *new)
{
	t_hist_cmd	*temp;

	if (first && *first)
	{
		temp = *first;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else if (first)
		*first = new;
}

t_hist_cmd	*create_histcmd(char *cmd)
{
	t_hist_cmd	*res;

	res = ft_calloc(1, sizeof(t_hist_cmd));
	res->cmd = cmd;
	res->next = NULL;
	return (res);
}

void	free_histcmd(t_hist_cmd *histcmd)
{
	if (histcmd)
	{
		if (histcmd->next)
			free_histcmd(histcmd->next);
		free(histcmd->cmd);
		free(histcmd);
	}
}