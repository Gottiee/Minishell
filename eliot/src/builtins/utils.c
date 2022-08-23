/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:07:52 by eedy              #+#    #+#             */
/*   Updated: 2022/08/23 19:37:04 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

char	*get_current_path(void)
{
	char	*buffer;

	// getcwd malloc buffer
	buffer = getcwd(NULL, 1024);
	if (buffer == NULL)
	{
		perror("-bash: pwd");
		return (NULL);
	}
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
