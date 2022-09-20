/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:51:34 by eedy              #+#    #+#             */
/*   Updated: 2022/09/20 14:15:37 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

void	read_here_doc(int *i, int *k, char *str_here_doc)
{
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
				printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", str_here_doc);
				return ;
			}
			add_char_here_doc(user_input, buff[0]);
			*i += 1;
		}
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
	else if (user_input->c)
	{
		user_in = concatenate_tstr(user_input);
		expend = get_txt(user_in);
		free(user_in);
		user_in = get_txt(str_here_doc);
		write(here->fd, expend, ft_strlen(expend) - ft_strlen(user_in) - 1);
		free(user_in);
		free(expend);
	}
	close(here->fd);
	here->fd = open(file_name, O_RDONLY, 0644);
	if (!user_input->c)
		free(user_input);
	else
		free_tstr(user_input);
	return (0);
}
