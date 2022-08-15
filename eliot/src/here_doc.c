/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:25:43 by eedy              #+#    #+#             */
/*   Updated: 2022/08/15 14:33:56 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eliot.h"

/*
	- creer un nouveau t_str qui va stocker ce que l'utilisteur va lui envoyer
	- changer la fonction cmp pour qu'elle compare les char de la list en partant de k element de la list
	- implementer le here doc
	- free str_here_doc
	- free le nom du fichier
	- unlik les fichiers 
	- free la nouvelle list chainee;
*/

int		here_doc(t_list_pipex *here)
{
	char	buff[2];
	int		i;
	int		k;
	char	*str_here_doc;
	t_str	*user_input;
	char	*file_name;

	i = 0;
	k = i;
	user_input = malloc(sizeof(t_str));
	str_here_doc = concatenate_tstr(here->str_pipex);
	if (!user_input || !str_here_doc)
	{
		free(str_here_doc);
		free(user_input);
		return (-1);
	}
	while (i == 0 || !cmp(str_here_doc, user_input, k))
	{
		k = i;
		buff[0] = '\0';
		while (buff[0] != '\n')
		{
			read(0, buff, 1);
			add_char_here_doc(user_input, buff[0]);
			i ++;
		}
	}
 	// je dois creer un moyen stocker des fichiers donc le nom et le fd qui l'as open
	file_name = random_file_name();
	here->file_name = file_name;
	here->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	free(str_here_doc);
	return (-1);
}

char	*random_file_name(void)
{
	char	*file_name;
	int		i;

	i = -1;
	file_name = malloc(sizeof(char) * 11);
	file_name[10] = '\0';
	while (++i < 10)
		file_name[i] = (char)gen_char();
	return (file_name);
}

int	gen_char(void)
{
	char	buff[4];
	int		nbr;
	int		fd;
	
	fd = open("/dev/random", O_RDONLY);
	if (fd < -1)
		return(-1);
	read(fd, buff, 4);
	nbr = *(int *)buff;
	if (nbr < 0)
		nbr++;
	if (nbr < 0)
		nbr *= -1;
	close(fd);
	return ('a' + nbr % 26);
}

int	cmp(char *s1, t_str *start, int k)
{
	int		i;
	t_str	*tmp;

	i = -1;
	tmp = start;
	// verifie que user exist
	if (!start)
		return (0);
	// se place sur le debut de la lettre
	while (++i < k)
		tmp = tmp->next;	
	i = 0;
	while (s1[i])
	{
		if (s1[i] != tmp->c)
			return (0);
		i ++;
		tmp = tmp->next;
	}
	if (tmp->c == '\n')
		return (1);
	return (0);
}
