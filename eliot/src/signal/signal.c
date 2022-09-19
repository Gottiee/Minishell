/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:10:56 by eedy              #+#    #+#             */
/*   Updated: 2022/09/19 14:47:30 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	prompt_signal(int sig)
{
	if (sig == SIGINT)
	{
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
		free_lclvar(generate_envvar_list(NULL));
		rl_clear_history();
		exit(1);
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
	signal(SIGQUIT, &signal_exit);
}
