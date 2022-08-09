NAME  = minishell

SRC_DIR = src/

BONUS_SRC_DIR = src_bonus/

SRC_FILES = main prompt cmd_type parsing t_local_var t_str operation utils hist_cmd ../libft/*

SRC =	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g $< -o $@

LIB = -lreadline

all: $(NAME)

$(NAME) :
	$(CC) $(SRC) -o $(NAME) $(LIB) -g

debug: $(NAME_DEBUG)


%.o: %.c
	$(CC) $(FLAGS)

clean :
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re : fclean all
