/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 02:30:59 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/29 17:43:27 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//pipex(argv[1], NULL);
	signal_handle();
	//pipex(argv[1], envp);
	start_prompt(envp);
	//cd(argv[1]);
	return (0);
}
