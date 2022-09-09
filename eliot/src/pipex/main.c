/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 02:30:59 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/09 14:03:29 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal_handle();
	start_prompt(envp);
	return (0);
}
