/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 02:30:59 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/20 15:25:29 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	g_return_value;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_return_value = 0;
	signal_handle();
	start_prompt(envp);
	return (0);
}
