/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:37:35 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/09 18:13:47 by tokerman         ###   ########.fr       */
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

t_lcl_var	*generate_envvar_list(char **envp)
{
	int	i;
	t_lcl_var	*res;
	t_lcl_var	*temp;

	i = 0;
	res = NULL;
	while (envp && envp[i] != NULL)
	{
		add_back_lclvar(&res, create_lclvar(envp[i], NULL, NULL));
		i++;
	}
	return (res);
}

/*
Prompt qui recupere l'entree de l'utilisateur et de lancer les commandes necessaire
Mettre plusieurs read jusqua un \n pour lire tout les caractere (bsq)
*/
void	start_prompt(char **envp)
{
	char	*res;
	char	*prt;
	t_lcl_var	*lclvar;
	t_lcl_var	*envvar;
	t_hist_cmd	*histcmd;
	
	res = malloc(10000);
	ft_bzero(res, 10000);
	lclvar = NULL;
	histcmd = NULL;
	envvar = generate_envvar_list(envp);
	while (1)
	{
		printf("Local variable :\n");
		t_lcl_var *temp;
		temp = lclvar;
		while (temp)
		{
			printf("%s=%s|\n", temp->name, temp->val);
			temp = temp->next;
		}
		ft_putstr_fd("Minishell$ ", 1);
		read(0, res, 10000);
		if (res[0] == '\n')
		{
			free(res);
			free_lclvar(lclvar);
			free_lclvar(envvar);
			free_histcmd(histcmd);
			break;
		}
		//Vrai commande a envoyer au parsing et a pipex
		prt = clear_str(res);
		add_back_histcmd(&histcmd, create_histcmd(prt));
		//Envoyer au parsing
		parsing(prt, &lclvar, &envvar);
		ft_bzero(res, 10000);
	}	
}
