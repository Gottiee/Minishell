/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:07:52 by eedy              #+#    #+#             */
/*   Updated: 2022/09/19 15:00:43 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

char	*get_current_path(void)
{
	char		*buffer;
	t_lcl_var	*envvar;
	t_lcl_var	*envpwd;

	buffer = getcwd(NULL, 1024);
	if (buffer == NULL)
	{
		envvar = generate_envvar_list(NULL);
		envpwd = get_lclvar_by_name(envvar, "PWD");
		if (envpwd)
		{
			buffer = ft_strdup(envpwd->val);
			if (!buffer)
				return (NULL);
		}
		else
		{
			buffer = malloc(sizeof(char) * 2);
			buffer[0] = '.';
			buffer[1] = '\0';
		}
	}
	change_envvar_val("PWD", buffer);
	return (buffer);
}

void	ls(char	*path)
{
	DIR				*dir;
	struct dirent	*entity;

	dir = opendir(path);
	if (dir == NULL)
		return ;
	entity = readdir(dir);
	while (entity != NULL)
	{
		printf("%s\n", entity->d_name);
		entity = readdir(dir);
	}
	closedir(dir);
}
