#ifndef THEO_H
# define THEO_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	start_prompt();
int		cmd_type(char *cmd);
int		check_spe_char(char *cmd);
void 	parsing(char *cmd);

typedef struct s_str
{
	char	c;
	s_str	*next;
}	t_str;

#endif