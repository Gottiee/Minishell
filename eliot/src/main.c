/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 02:30:59 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/05 12:55:10 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/eliot.h"

int	main(int argc, char **argv)
{
	(void)argc;
	pipex(argv[1], NULL);
	return (0);
}
