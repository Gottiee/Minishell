/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:51:34 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 14:05:56 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	read_here_doc(int *i, )
{
	while (*i == 0 || !cmp(str_here_doc, user_input, k))
	{
		k = *i;
		buff[0] = '\0';
		write(1, "> ", 2);
		while (buff[0] != '\n')
		{
			if (read(0, buff, 1) == -1)
			{
				perror("");
				return ;
				*i = -1;
			}
			add_char_here_doc(user_input, buff[0]);
			(*i) ++;
		}
		if (*i == -1)
			break;
	}
}

int	manage_filename(t_list_pipex *here, t_str *user_input, k, i)
{
	char	*file_name;
	char	*user_in;
	char	*expend;

	file_name = random_file_name();
	here->file_name = file_name;
	here->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here->quote_here_doc == 1)
		write_inside_file(user_input, here->fd, k);
	else
	{
		user_in = concatenate_tstr(user_input);
		expend = get_txt(user_in);
		write(here->fd, expend, ft_strlen(expend) - (i - k));
		free(user_in);
		free(expend);
	}
	close(here->fd);
	here->fd = open(file_name, O_RDONLY, 0644);
	free_tstr(user_input);
	return (0);
}
