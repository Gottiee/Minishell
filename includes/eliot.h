#ifndef ELIOT_H
# define ELIOT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <strings.h>
# include <sys/wait.h>
# include <errno.h>

/*	stucture pipex	*/
typedef struct s_pipex
{
	char	**pipe_splited;
	int		nbr_of_pipe;
	int		fd_pipe[2];

	//dans chaque process
	char	**cmd_splited;
	char	*cmd;
	int		return_value_var_global;
}				t_pipex;

/*          --- Fonctions qui gere pipex ---     */

/*Fichier: pipex.c*/
int	pipex(char *cmd, char *path);
int	manage_process(t_pipex *pipex, int index);
int	how_many_pipe(char **cmd);

/*Fichier: end_and_free.c*/
void	free_all_pipex(t_pipex *pipex);

/*          --- Fonctions qui gere split ---     */

/*Fichier: split.c*/
static int			get_nb_word(char const *s, char c);
static int			get_len_word(char const *s, char c, int index);
static const char	*get_pointer_word(char const *s, char c, int index);
static void			free_all(char ***tabl);
char				**ft_split(char const *s, char c);

/*Fichier: utils.c*/

void	*ft_calloc(size_t count, size_t size);
static void	ft_strncpy(char *dest, const char *src, unsigned int n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
#endif
