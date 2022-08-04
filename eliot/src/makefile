NAME  = minishell

LIBFT = -L libft/ -lft

BONUS_NAME = minishell_bonus

SRC_DIR = src/

BONUS_SRC_DIR = src_bonus/

SRC_FILES = main \
pipex \
split \
end_and_free \
utils \
parsing_pipex

BONUS_SRC_FILES = 

SRC =	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(addsuffix .c, $(BONUS_SRC_FILES)))

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = gcc

FLAGS =  -g -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ)
	make -C ./libft
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) -g

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
