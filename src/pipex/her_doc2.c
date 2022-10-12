/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:51:34 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 16:23:54 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	read_here_doc(int *i, int *k, char *str_here_doc, t_str *user_input)
{
	char	buff[2];
	int		read_status;

	while (*i == 0 || !cmp(str_here_doc, user_input, *k))
	{
		*k = *i;
		buff[0] = '\0';
		write(1, "> ", 2);
		while (buff[0] != '\n')
		{
			read_status = read(0, buff, 1);
			if (read_status == -1)
			{
				perror("");
				return ;
			}
			if (read_status == 0)
			{
				printf("bash: warning: here-document delimited \
by end-of-file (wanted `%s')\n", str_here_doc);
				return ;
			}
			add_char_here_doc(user_input, buff[0]);
			*i += 1;
		}
	}
}

void	manage_exp(char *user_in, t_list_pipex *here, char *str_here_doc)
{
	char	*expend;

	user_in = concatenate_tstr(here->user_input);
	expend = get_txt(user_in);
	free(user_in);
	user_in = get_txt(str_here_doc);
	write(here->fd, expend, ft_strlen(expend) - ft_strlen(user_in) - 1);
	free(expend);
	free(user_in);
}

int	manage_filename(t_list_pipex *here, char *str_here_doc, int k)
{
	char	*file_name;
	char	*user_in;

	user_in = NULL;
	file_name = random_file_name();
	here->file_name = file_name;
	here->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here->quote_here_doc == 1)
		write_inside_file(here->user_input, here->fd, k);
	else if (here->user_input->c)
	{
		manage_exp(user_in, here, str_here_doc);
		free(user_in);
	}
	close(here->fd);
	here->fd = open(file_name, O_RDONLY, 0644);
	free(str_here_doc);
	if (!here->user_input->c)
		free(here->user_input);
	else
		free_tstr(here->user_input);
	return (0);
}
