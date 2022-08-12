/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:25:43 by eedy              #+#    #+#             */
/*   Updated: 2022/08/12 18:59:48 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

/*
	- creer un nouveau t_str qui va stocker ce que l'utilisteur va lui envoyer
	- changer la fonction cmp pour qu'elle compare les char de la list en partant de k element de la list
	- implementer le here doc
	- free str_here_doc
	- free la nouvelle list chainee;
*/

int		here_doc(t_list_pipex *here)
{
	char	buff[2];
	int		i;
	int		k;
	char	*str_here_doc;

	i = 0;
	k = i;
	str_here_doc = concatenate_tstr(here->lexeur);
	if (str_here_doc == NULL)
		return (-1);
	while (i == 0 || !cmp(str_here_doc, ))
	{
		
	}
}

int	cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i ++;
	}
	if (s2[i] == '\n')
		return (1);
	return (0);
}
