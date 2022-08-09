#ifndef ELIOT_H
# define ELIOT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <strings.h>
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
}				 t_list_pipex;

typedef struct s_pipex
{
	char	**pipe_splited;
	int		nbr_of_pipe;
	int		fd_pipe[2];

	//dans chaque process
	char	**cmd_splited;
	char	*cmd;
	int		return_value_var_global;
	int		fd[2];

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
void	del_list(t_pipex *pipex);

/*Fichier: fork_process.c*/

/*Fichier: parsing_pipex.c*/
int		lexeur_pipex(t_pipex *pipex, char *cmd);

/*Fichier: stuct_manage_pipex.c*/
t_list_pipex	*init_struct_pipex(void);
int	add_struct_pipex(t_list_pipex *start, int type);
void	del_list_pipex(t_list_pipex *start);
void	free_tstr(t_str *tstr);
int	add_char_pipex(t_list_pipex *start, char char_p);
void	print_struc(t_list_pipex *start);

#endif
