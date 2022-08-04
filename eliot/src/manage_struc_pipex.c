/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_struc_pipex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:54:53 by eedy              #+#    #+#             */
/*   Updated: 2022/08/04 17:07:22 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

void	init_struct_value(t_pipex pipex)
{
	pipex->nbr_of_here_doc = 0;	
	pipex->here_doc = NULL;
	pipex->i_start_here_doc = NULL;
	pipex->i_end_here_doc = NULL;
	pipex->nbr_of_infile = 0;
	pipex->infile = NULL;
	pipex->i_start_infile = NULL;
	pipex->i_end_infile = NULL;
	pipex->nbr_of_redirection = 0;
	pipex->i_start_rediction = NULL;
	pipex->i_end_rediction = NULL;
	pipex->nbr_of_dbl_redirection = 0;
	pipex->dbl_redirection = NULL;
	pipex->i_start_dbl_rediction = NULL;
	pipex->i_end_dbl_rediction = NULL;
}
