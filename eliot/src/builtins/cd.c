/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:13:30 by eedy              #+#    #+#             */
/*   Updated: 2022/08/25 11:48:23 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	cd(char *directory)
{
	char		*buff;
	char		*path;
	t_lcl_var	*envvar;
	t_lcl_var	*envhome;

	buff = get_current_path();
	if (!buff)
		return (-1);
	if (!directory)
	{
		//coder cette partie  pour set up si cd est vide.
		// recuperer le nom du user pour le mettre a la place de "NAME"
		//fonction pour recuperer la liste chainee des variables d'env
		envvar = generate_envvar_list(NULL);
		//fonction qui cherche dans envvar une var d'env nomme HOME, envoie NULL si il trouve pas
		envhome = get_lclvar_by_name(&envvar, "HOME");
		if (envhome)
			chdir(envhome->val);//val c'est la valeur de la variable d'env
		else
			write(2, "bash: cd: HOME not set\n", 23);
		return (0);
	}
	if (directory[0] == '/' && !directory[1])
	{
		chdir("/mnt");
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
		write(2, ": ", 2);
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
