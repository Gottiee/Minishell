/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:57:58 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/04 19:52:44 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

/*
si presence de \ ou de "' non fermer ou de ; dans la cmd return 0
sinon return 1 

nb_dquotes == nombre de double quotes
nb_squotes == nombre de simple quotes
*/
int	check_spe_char(char *cmd)
{
	int	nb_dquotes;
	int	nb_squotes;

	nb_dquotes = 0;
	nb_squotes = 0;
	while (*cmd)
	{
		if (*cmd == '"' && nb_squotes % 2 == 0)
			nb_dquotes++;
		else if (*cmd == '\'' && nb_dquotes % 2 == 0)
			nb_squotes++;
		else if (*cmd == '\\' && (nb_dquotes % 2 == 0 && nb_squotes % 2 == 0))
			return (0);
		else if (*cmd == ';' && (nb_dquotes % 2 == 0 && nb_squotes % 2 == 0))
			return (0);
		cmd++;
	}
	if (nb_dquotes % 2 == 1 || nb_squotes % 2 == 1)
		return (0);
	return (1);
}

/*
Fonction qui regarde si la cmd est un declaration ou update de variable
*/
int	is_var_cmd(char *cmd)
{
	int	i;
	int	size;
	int quotes;

	i = 0;
	size = ft_strlen(cmd);
	quotes = 0;
	while (i < size && cmd[i] == ' ')//skip les espaces au debut
		i++;
	while (i < size && cmd[i] != '=')//le pointeur avnce jusqua '='
	{
		if (cmd[i] == '"' || cmd[i] == '\'' || cmd[i] == ' ')
			return (0);
		i++;
	}
	if (i == 0 || cmd[i - 1] == ' ')//verifi si le egal est pas le premier caractere apres les espaces du debut
		return (0);
	i++;
	if (i >= size)//verifi si il n'y a rien apres le egal
		return (0);
	if (i < size && (cmd[i] == '"' || cmd[i] == '\''))//verifi si il y a une quotes apres le egal et le prend en compte
		quotes = '"' - 33;
	if (i < size && cmd[i] == ' ')//si il n'y a pas un espace apres le egal
		return (0);
	while (i < size)//parcours jusqua fermer la quote ou jusqua ce qu'il y ai un espace si il n'y pas de quote
	{
		if (quotes > 0 && cmd[i] - 33 == quotes && cmd[i - 1] != '\\' && cmd[i - 1] != '=' )
			break;
		if (cmd[i] == ' ' && quotes == 0)
			break;
		i++;
	}
	i++;
	while (i < size)//verifi qu'il n'y a pas de caractere a part espace apres la fin de la valeur de la var
		if (cmd[i++] != ' ')
			return (0);
	return (1);
}

/*
fonction qui va verifier si il n'y pas d'erreur
	et qui va clean la cmd
*/
void parsing(char *cmd)
{
	if (check_spe_char(cmd) == 0)
		return ;
	printf("Is var %i\n", is_var_cmd(cmd));
	if (is_var_cmd(cmd))
	{
		t_lcl_var *var;

		var = create_lclvar(cmd);
		free_lclvar(var);
		//l'ajouter au dictionnaire de variables locales
	}
	else
	{
		//enlever la declaration de variable si il y en a une au milieu de pipi (ok=89 | ls) (le remplacer par "echo ''")
		//si c'est avec une autre cmd(ex : ls ok=89) le laisser car c'est un 
			//parametre de cmd et pas une declaration de variable
	}
}