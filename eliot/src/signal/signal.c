/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:10:56 by eedy              #+#    #+#             */
/*   Updated: 2022/08/29 16:36:05 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	prompt_signal(int sig)
{
	char	*res;
	char	*path;
	
	if (sig == SIGINT)
	{
		printf("\n");
		path = get_rdln_message();
		res = readline(path);
		free(path);
		if (cmd_type(res) == -6)
		{
			free(res);
			free_lclvar(generate_envvar_list(NULL));
			rl_clear_history();
			break;
		}
		add_history(res);
		parsing(res, envp);
		free(res);
	}
}

void	signal_handle(void)
{
	// si ctrl-c alors nouveaux prompt
	signal(SIGINT, &prompt_signal);
	// si ctrl-\ alors il est ignoree
	signal(SIGQUIT, SIG_IGN);
}
