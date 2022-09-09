/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:07:52 by eedy              #+#    #+#             */
/*   Updated: 2022/09/09 14:02:56 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

char	*get_current_path(void)
{
	char	*buffer;
	t_lcl_var	*envvar;
	t_lcl_var	*envpwd;

	// getcwd malloc buffer
	buffer = getcwd(NULL, 1024);
	if (buffer == NULL)
	{
		/*chercher dans l'env pwd*/
		envvar = generate_envvar_list(NULL);
		envpwd = get_lclvar_by_name(&envvar, "PWD");
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
		}
	}
	/*avant de return il faut que je sauvegarde paht dans PWD
	 - il faut que je verifie que pwd exist, s'il n 'existe pas rien faire;
	 - s'il existe le modifier;
	 */
	return (buffer);
}

void	ls(char	*path)
{
	// ouvrir un structure dir qui va stocker les infos de tout ce qu'il y a dans "x" directory
	DIR				*dir;
	struct dirent	*entity;

	dir = opendir(path);
	if (dir == NULL)
		return ;
	//entity est une autre stuct qui peut lire les données de DIR 
	entity = readdir(dir);
	// boucle pour lires les donnees de DIR 
	while (entity != NULL)
	{
		printf("%s\n", entity->d_name);
		entity = readdir(dir);
	}

	//end close and free
	closedir(dir);
}
