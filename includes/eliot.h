/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eliot.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:43:55 by eedy              #+#    #+#             */
/*   Updated: 2022/10/11 17:24:30 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <dirent.h>
# include <signal.h>
# include "theo.h"
# include "minishell.h"

# define HERE_DOC 1
# define INFILE 2
# define OUTFILE 3
# define DBL_OUTFILE 4
# define CMD 5
# define PIPE 6
# define HERE 7
# define SIG -2

/*	stucture pipex	*/

typedef struct s_pipe_lexeur
{
	int	*pipe;
	int	*tchque_pipe;
}	t_pipe_lexeur;

typedef struct s_list_pipex
{
	struct s_list_pipex	*next;
	t_str				*str_pipex;
	int					type;
	int					quote_here_doc;
	int					fd;
	char				*file_name;
	t_str				*user_input;
}	t_list_pipex;

typedef struct s_pipex
{
	char			**pipe_splited;
	int				nbr_of_pipe;
	int				**fd_pipe;
	char			**cmd_tab_exec;
	int				nbr_cmd;
	char			*cmd_path;
	char			*cmd_with_path;
	t_list_pipex	*lexeur;
}	t_pipex;

typedef struct s_manage
{
	t_list_pipex	*tmp;
	int				fd_infile;
	int				fd_outfile;
	char			*full_path;
	int				builtin;
	int				exec_status;
	int				i;
}	t_manage;

typedef struct s_man2
{
	int		i;
	int		*id;
	int		index_process;
	int		wstatus;
	int		status;
	int		pid;
	char	*status_char;
	int		exit_status;
}	t_man2;

typedef struct s_man3
{
	int		pid;
	int		fd[2];
	char	buffer[2];
	char	buff[4];
	int		i;
	int		cd_status;
	int		wstatus;
	int		status;
}	t_man3;

typedef struct s_cd
{
	t_list_pipex	*tmp;
	int				pid2;
	int				index_process;
	int				builtin;
	int				cd_status;
	int				bolo;
	int				wstatus;
	int				i;
	int				status;
	int				cmd_status;
}	t_cd;

//extern int		g_return_value;

/*          --- Fonctions qui gere pipex ---     */

/*Fichier: pipex.c*/
int				pipex2(char **env, int fd[2], t_pipex *pipex);
int				pipex(char *cmd, char **env);
int				manage_process(t_pipex *pipex, int index, char	**env);
int				how_many_pipe(char **cmd);
int				do_cd(t_pipex *pipex);

/*Fichier: pipex2.c*/
void			manage_process2(t_pipex *pipex, t_manage *man, char **env);
int				manage_process1(t_manage *man, int index, t_pipex *pipex);
int				free_man(t_manage *man, t_pipex *pipex);
int				lex_pipe(t_pipex *pipex, t_man2 *man, int fd[2]);
int				free_man(t_manage *man, t_pipex *pipex);

/*Fichier: pipex3.c*/
int				creat_proccess(t_man2 *man, t_pipex *pipex, char **env);
void			wait_process(t_pipex *pipex, t_man2 *man);
int				wait_child_do_cd(t_man3 *man, t_pipex *pipex);
int				first_fork(t_man3 *man, char *cmd, t_pipex *pipex, char **env);

/*Fichier: pipex4.c*/
void			ty_nor(t_man3 *man, t_pipex *pipex);
int				cd1(t_pipex *pipex, t_cd *cd);
void			cd2(t_pipex *pipex, t_cd *cd);
void			export_expend(t_pipex *pipex, t_cd *cd);

/*Fichier: pipex5.c*/
int				expend_first(t_man3 *man);

/*Fichier: end_and_free.c*/
void			free_all_pipex(t_pipex *pipex);
int				del_list(t_pipex *pipex, int ok);
void			free_cmd_tab(t_pipex *pipex);
void			free_all_path(char **path);
void			close_all_fd(int fd_outfile, int fd_infile, t_pipex *pipex);

/*Fichier: stuct_manage_pipex.c*/
t_list_pipex	*init_struct_pipex(void);
int				add_struct_pipex(t_list_pipex *start, int type);
void			del_list_pipex(t_list_pipex *start, int ok);
void			free_tstr(t_str *tstr);
int				add_char_pipex(t_list_pipex *start, char char_p);
void			add_bolo_here_doc(t_list_pipex *start);

/*Fichier: stuct_manage_2.c*/
char			*concatenate_tstr(t_str *node);
int				add_char_here_doc(t_str *start, char char_p);

/*Fichier: lexeur_pipex.c*/
void			lexeur_front_chevron(t_pipex *pipex, char *cmd, int *i);
void			lexeur_back_chevron(t_pipex *pipex, char *cmd, int *i);
void			pipe_lexeur(t_pipex *pipex, \
char *cmd, int *i, t_pipe_lexeur lex);
int				quote_add_char(t_pipex *pipex, char *cmd, int *i, int quote);

/*Fichier: lexeur_pipex2.c*/
void			lexeur_cmd(t_pipex *pipex, char *cmd, int *i);
int				lexeur_pipex(t_pipex *pipex, char *cmd);
void			lexeur_back_chevron2(t_pipex *pipex, char *cmd, int *i);
void			lexeur_front_chevron2(t_pipex *pipex, char *cmd, int *i);

/*Fichier: parsing_pipex.c*/
int				paring_pipex(t_list_pipex *start);
int				print_error_syntax(t_list_pipex *tmp);
int				parsing_pipex2(t_list_pipex *tmp);

/*Fichier: here_doc.c*/
int				here_doc(t_list_pipex *here);
int				cmp(char *s1, t_str *start, int k);
int				gen_char(void);
char			*random_file_name(void);
void			write_inside_file(t_str *user_input, int fd, int k);

/*Fichier: her_doc2.c*/
void			read_here_doc(int *i, int *k, \
char *str_here_doc, t_str *user_input);
int				manage_filename(t_list_pipex *here, char *str_here_doc, int k);

/*Fichier: fork_process.c*/
t_list_pipex	*actual_pipe(t_list_pipex *lexeur, int index);
char			**creat_tab_exec(t_list_pipex *lexeur, t_pipex *pipex);
char			*testing_path(t_list_pipex *lexeur);
int				find_path(char *full_path, t_pipex *pipex);
char			*is_path_exist(t_pipex	*pipex);

/*Fichier: fork_process2.c*/
int				while_find_path(int path_size, \
char **all_path, t_pipex *pipex, char *path);
char			**cmd_tab_exec_length(int *cmd, t_list_pipex *tmp);
int				infile_type2(int *count_infile, int id, t_list_pipex *tmp);
void			here_expension(int *count_infile, t_list_pipex *tmp, int id);

/*Fichier: get_file.c*/
int				outfile_type(t_list_pipex *tmp);
int				infile_type(t_list_pipex *tmp);
int				get_infile(t_list_pipex *lexeur, int index, t_pipex *pipex);
int				get_outfile(t_list_pipex *lexeur, int index, t_pipex *pipex);

/*          --- Fonctions qui gere les builtins---     */

/*Fichier: cd.c*/
int				ft_cd(char **directory);
char			*conca_str(char *str1, char *str2);

/*Fichier: utils.c*/
void			ls(char *path);
// renvoie un pointeur sur chaine de caractere malloc contenant le path actuell 
char			*get_current_path(void);

/*Fichier: pwd.c*/
int				pwd(void);

/*Fichier: builtins_manage.c*/
void			do_builtins(int builtin, char **cmd_tab_exec);

/*          --- Fonctions qui gere les signaux---     */

/*Fichier: signal.c*/
void			signal_handle(void);
void			prompt_signal(int sig);
void			signal_handle_fork(int sig);
void			signal_exit(int sig);
#endif
