NAME  = minishell

LIBFT = -L libft/ -lft

BONUS_NAME = minishell_bonus

SRC_DIR = src/

BONUS_SRC_DIR = src_bonus/

SRC_FILES = pipex/main \
pipex/pipex \
pipex/end_and_free \
pipex/lexeur_pipex \
pipex/fork_process \
pipex/struct_manage_pipex \
pipex/pipex_parsing \
pipex/here_doc \
builtins/cd \
builtins/utils \
builtins/pwd \
signal/signal \
../../theo/src/prompt \
../../theo/src/cmd_type \
../../theo/src/parsing \
../../theo/src/txt_trad \
../../theo/src/t_local_var \
../../theo/src/t_str \
../../theo/src/utils \
../../theo/src/hist_cmd

BONUS_SRC_FILES = 

SRC =	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(addsuffix .c, $(BONUS_SRC_FILES)))

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra -g -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ)
	make -C ./libft
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) -g -lreadline

debug: $(NAME_DEBUG)


%.o: %.c
	$(CC) $(FLAGS)

clean :
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	make clean -C ./libft

fclean : clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make fclean -C ./libft

bonus: $(BONUS_NAME)

re : fclean all


$(BONUS_NAME) : $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -o $(BONUS_NAME)

.PHONY: all clean fclean phony bonus re
