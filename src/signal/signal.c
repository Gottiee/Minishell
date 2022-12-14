/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:10:56 by eedy              #+#    #+#             */
/*   Updated: 2022/10/19 11:13:26 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	prompt_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_return_value = 130;
		change_envvar_val("?", "130");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_exit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_return_value = 131;
		write(2, "Quit (core dumped)\n", 20);
		exit(131);
	}
}

void	signal_handle_fork(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

void	signal_handle(void)
{
	signal(SIGINT, &prompt_signal);
	signal(SIGQUIT, SIG_IGN);
}
