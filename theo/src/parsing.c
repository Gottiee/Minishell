/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:57:58 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/04 15:29:29 by tokerman         ###   ########.fr       */
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

int	get_size_cmd_without_quotes(char *cmd)
{
	int	size;
	int	i;
	int	s_cmd;

	s_cmd = ft_strlen(cmd);
	size = 0;
	i = 0;
	while (cmd[i] == ' ' && i++ < s_cmd)
		cmd++;
	while (cmd[i] != ' ' && i < s_cmd)
	{
		if (*cmd != '\'' && *cmd != '"')
			size++;
		i++;
	}
	while (cmd[i] != '\0' && i++ < s_cmd)
		size++;
	return (size);
}
/*
fonction qui va enlever les quotes de la cmd
*/
char	*remove_quotes_frm_cmd(char	*cmd)
{
	int	size;
	int i;
	char	*res;
	int	word;
	t_str	*temp;

	size = get_size_cmd_without_quotes(cmd);
	res = ft_calloc(size + 1, sizeof(char));
	i = 0;
	while (*cmd == ' ')
		cmd++;
	word = 0;
	while (*cmd)
	{
		if (*cmd == ' ')
			word = 1;
		if (*cmd != '\'' && *cmd != '"' || word)
			res[i++] = *cmd;
		cmd++;
	}
	return (res);
}

/*
fonction qui va verifier si il n'y pas d'erreur
	et qui va clean la cmd
*/
void parsing(char *cmd)
{
	if (check_spe_char(cmd) == 0)
		return (NULL);
	remove_quotes_frm_cmd(cmd);
}