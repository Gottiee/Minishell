/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:57:58 by tokerman          #+#    #+#             */
/*   Updated: 2022/09/22 16:11:58 by tokerman         ###   ########.fr       */
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
fonction qui va verifier si il n'y pas d'erreur
	et qui va clean la cmd
*/
char	*parsing(char *cmd, char **envp)
{
	t_lcl_var	*temp;
	t_lcl_var	*envlst;
	char		*cmd_expended;

	if (check_spe_char(cmd) == 0)
	{
		envlst = generate_envvar_list(NULL);
		temp = get_lclvar_by_name(&envlst, "?");
		free(temp->val);
		temp->val = ft_strdup("2");
		printf("bash: error syntax\n");
	}
	else
	{
		cmd_expended = trad_cmd(cmd);
		g_return_value = pipex(cmd_expended, envp);
		free(cmd_expended);
		envlst = generate_envvar_list(NULL);
		temp = get_lclvar_by_name(&envlst, "?");
		free(temp->val);
		temp->val = ft_itoa(g_return_value);
	}
	return (NULL);
}
