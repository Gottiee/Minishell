#ifndef ELIOT_H
# define ELIOT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"
# include "minishell.h"

# define HERE_DOC 1
# define INFILE 2
# define OUTFILE 3
# define DBL_OUTFILE 4
# define CMD 5
# define PIPE 6

/*	stucture pipex	*/

typedef	struct s_pipe_lexeur
{
	int	*pipe;
	int	*tchque_pipe;
} t_pipe_lexeur;

typedef struct s_str
{
	char	c;
	struct s_str	*next;
} t_str;

typedef struct s_list_pipex
{
	struct s_list_pipex	*next;
	t_str				*str_pipex;
	int					type; // stock ce que c'est : here doc ... avec le define la haut
	int					quote_here_doc;
	int					fd;
	char				*file_name;
}				 t_list_pipex;

typedef struct s_pipex
{
	char	**pipe_splited;
	int		nbr_of_pipe;
	int		fd_pipe[2];

	//dans chaque process
	char	**cmd_tab_exec;
	int		nbr_cmd;
	char	*cmd_path;
	int		return_value_var_global;

	//parsing de la cmd
	t_list_pipex	*lexeur;
	
}				t_pipex;


/*          --- Fonctions qui gere pipex ---     */

/*Fichier: pipex.c*/
int		pipex(char *cmd, char *path);
int		manage_process(t_pipex *pipex, int index);
int		how_many_pipe(char **cmd);

/*Fichier: end_and_free.c*/
void	free_all_pipex(t_pipex *pipex);
int		del_list(t_pipex *pipex);
void	free_cmd_tab(t_pipex *pipex);

/*Fichier: stuct_manage_pipex.c*/
t_list_pipex	*init_struct_pipex(void);
int	add_struct_pipex(t_list_pipex *start, int type);
void	del_list_pipex(t_list_pipex *start);
void	free_tstr(t_str *tstr);
int	add_char_pipex(t_list_pipex *start, char char_p);
void	print_struc(t_list_pipex *start);
void	add_bolo_here_doc(t_list_pipex *start);
char	*concatenate_tstr(t_str *node);
int	add_char_here_doc(t_str *start, char char_p);

/*Fichier: lexeur_pipex.c*/
int		lexeur_pipex(t_pipex *pipex, char *cmd);
void	lexeur_front_chevron(t_pipex *pipex, char *cmd, int *i);
void	lexeur_back_chevron(t_pipex *pipex, char *cmd, int *i);
void	lexeur_cmd(t_pipex *pipex, char *cmd, int *i);
void	pipe_lexeur(t_pipex *pipex, char *cmd, int *i, t_pipe_lexeur lex);
void	quote_add_char(t_pipex *pipex, char *cmd, int *i, int quote);

/*Fichier: parsing_pipex.c*/
int	paring_pipex(t_list_pipex *start);
int	print_error_syntax(t_list_pipex *tmp);
int	parsing_pipex2(t_list_pipex *tmp);


/*Fichier: here_doc.c*/
int		here_doc(t_list_pipex *here);
int	cmp(char *s1, t_str *start, int k);
int	gen_char(void);
char	*random_file_name(void);
void	write_inside_file(t_str *user_input, int fd, int k);

/*Fichier: fork_process.c*/
t_list_pipex	*actual_pipe(t_list_pipex *lexeur, int index);
int				get_infile(t_list_pipex *lexeur, int index, t_pipex *pipex);
int				get_outfile(t_list_pipex *lexeur, int index, t_pipex *pipex);
char			**creat_tab_exec(t_list_pipex *lexeur, t_pipex *pipex);

#endif
