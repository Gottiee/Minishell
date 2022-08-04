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

/*	stucture pipex	*/

typedef struct s_list_pipex
{
	struct s_list_pipex	*next;
	struct t_str		*str_pipex;
	int					start;
	int					end;
	int					index;
} t_list_pipex;

typedef struct s_pipex
{
	char	**pipe_splited;
	int		nbr_of_pipe;
	int		fd_pipe[2];

	//dans chaque process
	char	**cmd_splited;
	char	*cmd;
	int		return_value_var_global;


	//parsing de la cmd
	t_list_pipex	*here_doc;
	t_list_pipex	*infile ;
	t_list_pipex	*redirection ;
	t_list_pipex	*dbl_redirection ;
	t_list_pipex	*cmd;
	
}				t_pipex;



/*          --- Fonctions qui gere pipex ---     */

/*Fichier: pipex.c*/
int	pipex(char *cmd, char *path);
int	manage_process(t_pipex *pipex, int index);
int	how_many_pipe(char **cmd);

/*Fichier: end_and_free.c*/
void	free_all_pipex(t_pipex *pipex);

#endif
