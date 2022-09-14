/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:39:25 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/14 13:12:41 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

/*
Fonction qui regarde si la cmd est un declaration ou update de variable
*/
/*
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
*/
int		correct_syntax(char *cmd)
{
	t_str	*name_tstr;
	int		i;
	int		size;
	char	*name;
	
	name_tstr = NULL;
	while (*cmd && *cmd != '=')
		add_back_tstr(&name_tstr, create_tstr(*cmd++));
	if (!*cmd)
	{
		free_tstr(name_tstr);
		return (0);
	}
	cmd++;
	name = get_str_with_tstr(name_tstr);
	size = ft_strlen(name);
	if ((size == 1 && name[0] == '_') || get_type_val(name) == 0)
	{
		free(name);
		return (-1);
	}
	i = 0;
	while (i < size)
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			free(name);
			return (-1);
		}
		i++;
	}
	free(name);
	return (1);
}


//pourvoir export plusieurs choses
int	cmd_export(char **cmd)
{
	t_lcl_var	*var;
	t_lcl_var	*temp_env;
	t_lcl_var	*envvar;
	int			i;

	envvar = generate_envvar_list(NULL);
	i = 1;
	while (cmd[i])
	{
		if (correct_syntax(cmd[i]) == 1)
		{
			var = create_lclvar(cmd[i]);
			temp_env = get_lclvar_by_name(&envvar, var->name);
			if (temp_env != NULL)
			{
				temp_env->val = ft_strdup(var->val);
				free_lclvar(var);
			}
			else
				add_back_lclvar(&envvar, var);
		}
		else if (correct_syntax(cmd[i]) == -1)
		{
			printf("Error syntax\n");//bash: export: `=trt': not a valid identifier
			return (1);
		}
		i++;
	}
	return (0);
}