/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:37:35 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/29 16:06:12 by eedy             ###   ########.fr       */
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
	static t_lcl_var	*res;

	if (res == NULL)
	{
		i = 0;
		res = NULL;
		while (envp && envp[i] != NULL)
		{
			add_back_lclvar(&res, create_lclvar(envp[i], NULL, NULL));
			i++;
		}	
	}
	return (res);
}

t_lcl_var	*generate_lclvar_list()
{
	static t_lcl_var	*res;

	return (res);
}

char	*get_rdln_message()
{
	char	*path;
	char	*res;

	path = get_current_path();
	res = ft_strjoin("Minishell:", path);
	free(path);
	path = ft_strjoin(res, "$ ");
	free(res);
	return (path);
}

/*
Prompt qui recupere l'entree de l'utilisateur et de lancer les commandes necessaire
Mettre plusieurs read jusqua un \n pour lire tout les caractere (bsq)
*/
void	start_prompt(char **envp)
{
	char	*res;
	char	*path;
	t_lcl_var	*lclvar;
	t_lcl_var	*envvar;

	res = NULL;
	lclvar = NULL;
	envvar = generate_envvar_list(envp);
	while (1)
	{
	/*printf("Local variable :\n");
		t_lcl_var *temp;
		temp = lclvar;
		while (temp)
		{
			printf("|%s=%s|\n", temp->name, temp->val);
			temp = temp->next;
		}
		printf("Emv variable :\n");
		temp = envvar;
		while (temp)
		{
			printf("|%s=%s|\n", temp->name, temp->val);
			temp = temp->next;
		}*/	
		
		path = get_rdln_message();
		res = readline(path);
		free(path);
		if (cmd_type(res) == -6)
		{
			free(res);
			free_lclvar(lclvar);
			free_lclvar(envvar);
			rl_clear_history();
			break;
		}
		else if (cmd_type(res) == -7)
			cmd_echo(res, &lclvar, &envvar);
		else if (cmd_type(res) == -3)
			cmd_export(res, &lclvar, &envvar);
		printf("cmd type : %i\n", cmd_type(res));
		add_history(res);
		parsing(res, &lclvar, &envvar, envp);
		free(res);
	}	
}
