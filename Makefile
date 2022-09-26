# VARIABLES

NAME		= minishell
#NAME_BONUS	= pipex_bonus

LIB_DIR	 	= libft
LIB			= libft/libft.a

SRC_DIR		= src/
OBJ_DIR		= obj/
SUBDIR		= obj/pipex obj/builtins obj/signal obj/parsing_theo obj/struct
#BONUS_DIR	= src_bonus/

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g -I./srcs/includes -MMD -MP
ADDFLAGS	=  -L -lft -lreadline

RM			= rm -rf
AR			= ar rcs
SAN			= -fsanitize=address

# SOURCES

SRC_FILES = pipex/main \
pipex/pipex \
pipex/pipex2 \
pipex/pipex3 \
pipex/pipex4 \
pipex/end_and_free \
pipex/lexeur_pipex \
pipex/lexeur_pipex2 \
pipex/fork_process \
pipex/fork_process2 \
pipex/get_file \
pipex/struct_manage_pipex \
pipex/struc_manage2 \
pipex/pipex_parsing \
pipex/here_doc \
pipex/her_doc2 \
builtins/cd \
builtins/utils \
builtins/pwd \
builtins/builtins_manage \
builtins/echo \
builtins/env \
builtins/unset \
builtins/export \
signal/signal \
parsing_theo/cmd_type \
parsing_theo/parsing \
parsing_theo/txt_trad \
parsing_theo/utils \
struct/prompt \
struct/t_local_var2 \
struct/t_local_var \
struct/t_str2 \
struct/t_str 

C_FILES		=	$(addsuffix .c, $(SRC_FILES))
SRCS		=	$(addprefix $(SRC_DIR), $(C_FILES))
OBJS		=	$(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))
DEPS		=	$(OBJS:.o=.d)

#SRC_FILES_BONUS	=	main child pipes get_files get_cmd free heredoc error
C_BONUS			=	$(addsuffix _bonus.c, $(SRC_FILES_BONUS))
SRCS_BONUS		=	$(addprefix $(BONUS_DIR), $(C_BONUS))
OBJS_BONUS		=	$(addprefix $(OBJ_DIR), $(C_BONUS:.c=.o))
DEPS_BONUS		=	$(OBJS_BONUS:.o=.d)

#	 MANDATORY
all:		 $(LIB) obj $(NAME)
			

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $^ -o $@ $(LIB) $(ADDFLAGS) 
			@echo "$(RED)$(NAME) compiled !$(DEF_COLOR)"

$(OBJ_DIR)%.o:	 $(SRC_DIR)%.c 
			@$(CC) $(CFLAGS) $(ADDFLAGS) -c -o $@ $< 
			@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

#	BONUS
bonus:		$(LIB) $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
			@$(CC) $(CFLAGS) $(ADDFLAGS) $^ -o $(NAME_BONUS) $(LIB)
			@echo "$(RED)$(NAME_BONUS) BONUS compiled !$(CYAN)"

$(OBJ_DIR)%.o:	 $(BONUS_DIR)%.c 
			tamere
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) -c -o $@ $< 
			@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

$(LIB):
			@echo "$(MAGENTA)Creating libft files...$(CYAN)"
			@make -s -C ./libft

#	 RULES
obj:
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(SUBDIR)

clean:
			@make clean -C $(LIB_DIR)
			@$(RM) $(OBJ_DIR) $(DEPS_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(NAME_BONUS)
			@$(RM) -f $(LIB_DIR)/libft.a

re:			fclean
			@make all
			@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)!$(DEF_COLOR)"

.PHONY: all clean fclean re	

.SILENT: lib

-include $(DEPS)

# COLORS

NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
