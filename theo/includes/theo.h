#ifndef THEO_H
# define THEO_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_str
{
	char	c;
	struct s_str	*next;
}	t_str;

typedef struct s_lcl_var
{
	char	*name;
	void	*val;
	int		type;//1 = string 0 = long long int
	struct s_lcl_var	*next;
}	t_lcl_var;

void	start_prompt();
int		cmd_type(char *cmd);

//parsing
int		check_spe_char(char *cmd);
void 	parsing(char *cmd);
int		is_var_cmd(char *cmd);

//t_str
t_str	*create_tstr(char c);
void	add_back_tstr(t_str **first, t_str *new);

#endif