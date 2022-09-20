/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:25:43 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 14:04:19 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int		here_doc(t_list_pipex *here)
{
	char	buff[2];
	int		i;
	int		k;
	char	*str_here_doc;
	t_str	*user_input;

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
	user_input->c = '\0';
	read_here_doc();
	free(str_here_doc);
	return (manage_filename(here, user_input, k, i));
}

void	write_inside_file(t_str *user_input, int fd, int k)
{
	int		i;
	t_str	*tmp;

	tmp = user_input;
	i = -1;
	while (++i < k)
	{
		write(fd, &(tmp->c), 1);
		tmp = tmp->next;
	}
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
	
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < -1)
		return(-1);
	read(fd, buff, 4);
	nbr = *(int *)buff;
	if (!nbr)
		nbr = 'a';
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
