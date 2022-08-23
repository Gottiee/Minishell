/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:13:30 by eedy              #+#    #+#             */
/*   Updated: 2022/08/23 20:02:41 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	cd(char *directory)
{
	char	*buff;
	char	*path;

	buff = get_current_path();
	if (!buff)
		return (-1);
	if (!directory)
	{
		//coder cette partie  pour set up si cd est vide.
		chdir("/Users/eliot");
		return (0);
	}
	if (directory[0] == '/' && !directory[1])
	{
		write(2, "-bash: cd: /:No such file or directory\n", 39);
		return (0);
	}
	if (chdir(directory) == 0)
	{
	//	buff = get_current_path();
	//	printf("current path: %s\n", buff);
		return (0);
	}
	path = conca_str(buff, directory);
	if (!path)
		return (-1);
	if (chdir(path) == -1)
	{
		write(2, "-bash: cd: ", 11);
		write(2, directory, ft_strlen(directory));
		write(2, " :", 2);
		perror("");
		return (-1);
	}
	free(path);
	free(buff);
	return (0);
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
	path[i + 1]= '\0';
	return (path);
}
