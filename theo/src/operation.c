/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:44:01 by tokerman          #+#    #+#             */
/*   Updated: 2022/08/09 05:19:44 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/theo.h"

int	is_operation(char *val)
{
	char	*str;
	int		end;
	int		start;

	str = remove_dquotes(val);
	end = ft_strlen(str);
	end--;
	while (end > 0 && str[end] == ' ')
		end--;
	start = 0;
	while (start < end && str[start] == ' ')
		start++;
	if (end - start < 4)
	{
		free(str);
		return (0);
	}
	if (str[start] == '$' && str[start + 1] == '(' && str[start + 2] == '(' && str[end] == ')' && str[end - 1] == ')')
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

char	*operate(char *val, t_lcl_var **lclvar, t_lcl_var **envvar)
{
	//lancer les operations avec un echo dans execve pour recuperer le resultat
		//juste remplacer les variables locales et environnemental dans la cmd
}