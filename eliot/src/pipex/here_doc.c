/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:25:43 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 15:13:16 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	here_doc(t_list_pipex *here)
{
	int		i;
	int		k;
	char	*str_here_doc;

	i = 0;
	k = i;
	here->user_input = malloc(sizeof(t_str));
	here->user_input->c = '\0';
	str_here_doc = concatenate_tstr(here->str_pipex);
	if (!here->user_input || !str_here_doc)
	{
		free(str_here_doc);
		free(here->user_input);
		return (-1);
	}
	here->user_input->c = '\0';
	read_here_doc(&i, &k, str_here_doc, here->user_input);
	return (manage_filename(here, str_here_doc, k));
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
	file_name = ft_calloc(11, (sizeof(char)));
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
		return (-1);
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
	if (!start)
		return (0);
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
	if (!tmp || tmp->c == '\n')
		return (1);
	return (0);
}
