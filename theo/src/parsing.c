/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:57:58 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/27 20:57:48 by tokerman         ###   ########.fr       */
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
retourne 0 si le nom de la variable contient des characteres autre que que des lettres, des chiffres ou des uderscore
et retourne 1 sinon
+ gestion de quelque cas particulier faux
	le nom de la var c'est "_"
	le nom ne comporte que des chiffres
*/
int	check_lclvar_name(char *cmd)
{
	char	*name;
	int		i;
	int		size;
	
	name = get_name_var(cmd);
	size = ft_strlen(name);
	if ((size == 1 && name[0] == '_') || get_type_val(name) == 0)
	{
		free(name);
		return (0);
	}
	i = 0;
	while (i < size)
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
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
	while (i < size && cmd[i] != '=')//le pointeur avnce jusqua '='
		i++;
	if (i == 0 || cmd[i - 1] == ' ')//verifi si le egal est pas le premier caractere apres les espaces du debut
		return (0);
	i++;
	if (i >= size)//verifi si il n'y a rien apres le egal
		return (0);
	if (i < size && cmd[i] == ' ')//si il n'y a pas un espace apres le egal
		return (0);
	if (i < size && (cmd[i] == '"' || cmd[i] == '\''))//verifi si il y a une quotes apres le egal et le prend en compte
	{
		quotes = cmd[i];
		i++;
	}
	while (i < size)//parcours jusqua fermer la quote ou jusqua ce qu'il y ai un espace si il n'y pas de quote
	{
		if (quotes == 0 && (cmd[i] == '"' || cmd[i] == '\''))
			quotes = cmd[i];
		else if (quotes > 0 && cmd[i] == quotes)
			quotes = 0;
		else if (cmd[i] == ' ' && quotes == 0)
			break;
		i++;
	}
	i++;
	while (i < size)//verifi qu'il n'y a pas de caractere a part espace apres la fin de la valeur de la var
		if (cmd[i++] != ' ')
			return (0);
	return (check_lclvar_name(cmd));
}

/*
fonction qui gere la declaration d'une variable via une commande
ex : ok=89
*/
void	var_cmd(char *cmd, t_lcl_var **lclvar, t_lcl_var **envvar)
{
	t_lcl_var *var;
	t_lcl_var *temp_lcl;
	t_lcl_var *temp_env;

	var = create_lclvar(cmd, lclvar, envvar);
	temp_lcl = get_lclvar_by_name(lclvar, var->name);
	temp_env = get_lclvar_by_name(envvar, var->name);
	if (temp_lcl != NULL)
	{
		free(temp_lcl->val);
		temp_lcl->val = ft_strdup(var->val);
		free_lclvar(var);
	}
	else if (temp_env != NULL)
	{
		//modification de la variable d'environnement
	}
	else
		add_back_lclvar(lclvar, var);
}

/*
fonction qui va verifier si il n'y pas d'erreur
	et qui va clean la cmd
*/
char *parsing(char *cmd, t_lcl_var **lclvar, t_lcl_var **envvar)
{
	if (check_spe_char(cmd) == 0)
		return NULL;//retourner une erreur "Wrong syntax"
	if (is_var_cmd(cmd))
	{
		var_cmd(cmd, lclvar, envvar);
		return ("echo -n ''");
	}
	else
	{
		//enlever la declaration de variable si il y en a une au milieu de pipex (ok=89 ls) (l'enlever)
		//si c'est avec une autre cmd(ex : ls ok=89) le laisser car c'est un 
			//parametre de cmd et pas une declaration de variable

		//si il est dans une commande (ex ok=8 ls) // si il est au debut l'enlever et envoyer le reste a pipex
	}

	//utiliser cette fonction pour parser une commande apres l'autre
	//c'est pipex qui doit appeler cette commande
	//retourne la bonne commande (traduction de variable ou 
		//enlever les declarations de variables)
	//em plus le $? compte une declaration de variables reussit
	return (NULL);
}