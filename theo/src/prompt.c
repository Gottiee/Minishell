/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:37:35 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/04 19:47:05 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"


/*
Permet de retourner la bonne size de la str du read
*/
int		get_clear_size(char *str)
{
	int	size;
	
	size = -1;
	while (*str++ != '\0')
		size++;
	return (size);
}

/*
Permet de retourner la chaine de caractere de l'entree du read sans le /n et de la taille necessaire
*/
char	*clear_str(char *str)
{
	int	size;
	char	*res;

	size = get_clear_size(str);
	res = ft_calloc(size + 1, sizeof(char));
	while (size > 0)
	{
		res[size - 1] = str[size - 1];
		size--;
	}
	return (res);
}

/*
Prompt qui recupere l'entree de l'utilisateur et de lancer les commandes necessaire
Mettre plusieurs read jusqua un \n pour lire tout les caractere (bsq)
*/
void	start_prompt()
{
	char	*res;
	char	*prt;
	
	res = malloc(10000);
	ft_bzero(res, 10000);
	while (1)
	{
		ft_putstr_fd("Minishell$ ", 1);
		read(0, res, 10000);
		if (res[0] == '\n')
		{
			free(res);
			break;
		}
		//Vrai commande a envoyer au parsing et a pipex
		prt = clear_str(res);
		//Envoyer au parsing
		parsing(prt);
		free(prt);
		ft_bzero(res, 10000);
	}	
}
