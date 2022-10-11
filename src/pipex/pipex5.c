/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:20:12 by eedy              #+#    #+#             */
/*   Updated: 2022/10/11 17:24:12 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int expend_first(t_man3 *man)
{
	close(man->fd[1]);
	signal(SIGINT, &signal_handle_fork);
	waitpid(man->pid, &man->wstatus, 0);
	if (WEXITSTATUS(man->wstatus) == 2)
	{
		signal(SIGINT, &prompt_signal);
		return (-1);
	}
	return (0);
}
