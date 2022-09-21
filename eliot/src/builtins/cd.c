/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:13:30 by eedy              #+#    #+#             */
/*   Updated: 2022/09/21 17:18:18 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	free_path_cd(char *buff, char *path)
{
	free(path);
	free(buff);
}

int	cd_ext(char **directory, char *buff, char *path)
{
	if (directory[2])
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (1);
	}
	if (directory[1][0] == '/' && !directory[1][1])
	{
		chdir("/mnt");
		return (0);
	}
	path = conca_str(buff, directory[1]);
	if (!path)
		return (-1);
	if (chdir(path) == -1)
	{
		write(2, "bash: cd: ", 11);
		write(2, directory[1], ft_strlen(directory[1]));
		write(2, ": ", 2);
		perror("");
		free_path_cd(buff, path);
		return (1);
	}
	free_path_cd(buff, path);
	return (0);
}

int	ft_cd(char **directory)
{
	char		*buff;
	char		*path;
	t_lcl_var	*envvar;
	t_lcl_var	*envhome;

	path = NULL;
	buff = get_current_path();
	if (!buff)
		return (-1);
	if (!directory[1])
	{
		envvar = generate_envvar_list(NULL);
		envhome = get_lclvar_by_name(&envvar, "HOME");
		if (envhome)
		{
			chdir(envhome->val);
			free(buff);
			return (0);
		}
		else
			write(2, "bash: cd: HOME not set\n", 23);
		free(buff);
		return (1);
	}
	return (cd_ext(directory, buff, path));
}

char	*conca_str(char *str1, char *str2)
{
	char	*path;
	int		i;
	int		j;

	path = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!path)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		path[i] = str1[i];
	path[i] = '/';
	while (str2[++j])
		path[++i] = str2[j];
	path[i + 1] = '\0';
	return (path);
}
