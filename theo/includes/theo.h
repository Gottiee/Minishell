#ifndef THEO_H
# define THEO_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

# define CD 7
# define ECHO 8
# define EXPORT 9
# define PWD 10
# define UNSET 11
# define ENV 12
# define EXIT 13

typedef struct s_str
{
	char	c;
	struct s_str	*next;
}	t_str;
 
typedef struct s_lcl_var
{
	char	*name;
	char	*val;
	int		type;
	struct s_lcl_var	*next;
}	t_lcl_var;

void	signal_handle(void);
t_lcl_var	*generate_envvar_list(char **envp);
int			cmd_type(char *cmd);

//prompt
void		start_prompt(char **envp);

//export
void		cmd_export(char **cmd);

//echo
void		cmd_echo(char **cmd);

//parsing
int			check_spe_char(char *cmd);
char 		*parsing(char *cmd, char **envp);
int			is_var_cmd(char *cmd);

//t_str
t_str		*create_tstr(char c);
void		add_back_tstr(t_str **first, t_str *new);
char		*get_str_with_tstr(t_str *first);
t_str		*get_tstr_with_str(char *txt);
int			tstr_len(t_str *tstr);

//utils
char		*remove_dquotes(char *str);

//operation
int			is_operation(char *val);
char		*operate(char *val, t_lcl_var **lclvar, t_lcl_var **envvar);

//t_lcl_var
char		*get_name_var(char	*cmd);
int			get_type_val(char *text);
t_lcl_var	*create_lclvar(char	*cmd);
void		free_lclvar(t_lcl_var *var);
void		add_back_lclvar(t_lcl_var **first, t_lcl_var *new);
t_lcl_var	*get_lclvar_by_name(t_lcl_var **lclvar, char *tofind);

//txt_trad
char		*get_txt(char *cmd);

// renvoie un pointeur sur chaine de caractere malloc contenant le path actuell 
char		*get_current_path(void);

/*Fichier: pipex.c*/
int		pipex(char *cmd, char **env);
#endif
