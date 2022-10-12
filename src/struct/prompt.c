/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:37:35 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/26 12:07:29 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/theo.h"

/*
Permet de retourner la bonne size de la str du read
*/
int	get_clear_size(char *str)
{
	int	size;

	size = -1;
	while (*str++ != '\0')
		size++;
	return (size);
}

/*
Permet de retourner la chaine de caractere de l'entree 
	du read sans le /n et de la taille necessaire
*/
char	*clear_str(char *str)
{
	int		size;
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

char	**get_envp(char **envp)
{
	static char	**res;

	if (res == NULL)
		res = envp;
	return (res);
}

char	*get_rdln_message(void)
{
	char	*path;
	char	*res;

	path = get_current_path();
	res = ft_strjoin("Minishell:", path);
	free(path);
	path = ft_strjoin(res, "$ ");
	free(res);
	res = readline(path);
	free(path);
	return (res);
}

/*
Prompt qui recupere l'entree de l'utilisateur et 
	de lancer les commandes necessaire
Mettre plusieurs read jusqua un \n pour lire tout les caractere (bsq)
*/
void	start_prompt(char **envp)
{
	char	*res;

	res = NULL;
	generate_envvar_list(envp);
	get_envp(envp);
	while (1)
	{
		res = get_rdln_message();
		if (!res || cmd_type(res) == EXIT)
		{
			printf("exit\n");
			free(res);
			free_lclvar(generate_envvar_list(NULL));
			clear_history();
			break ;
		}
		if (ft_strlen(res) > 0)
		{
			add_history(res);
			parsing(res, envp);
		}
 		free(res);
	}	
}
