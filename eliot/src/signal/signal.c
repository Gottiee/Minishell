/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:10:56 by eedy              #+#    #+#             */
/*   Updated: 2022/08/25 13:04:23 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	prompt_signal(int sig)
{
	if (sig == SIGINT)
		printf("affichage d'un new prompte\n");
}

void	signal_handle(void)
{
	// si ctrl-c alors nouveaux prompt
	signal(SIGINT, &prompt_signal);
	// si ctrl-\ alors il est ignoree
	signal(SIGQUIT, SIG_IGN);
}
