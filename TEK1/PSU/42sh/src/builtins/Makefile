##
## EPITECH PROJECT, 2025
## 42sh
## File description:
## Makefile for builtins
##

CFLAGS += -Wall -Wextra -I../../include

SRC		=	history/handle_history.c		\
			alias/alias.c					\
			alias/handle_alias.c			\
			alias/unalias.c					\
			env/env.c						\
			env/setenv.c					\
			env/unsetenv.c					\
			cd/cd_tilde.c					\
			cd/get_home_user.c				\
			cd/my_getenv.c					\
			cd/my_cd.c						\
			exec/my_exit.c					\
			which_and_where/which.c			\
			which_and_where/where.c			\

OBJ = $(SRC:.c=.o)

NAME = ../../libs/libbuiltins.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "[-] Compiling $(NAME) [-]"
	@ar rc $(NAME) $(OBJ) >/dev/null
	@echo "Compilation done !"

clean:
	@echo "[!] Removing object files [!]"
	$(RM) $(OBJ)

fclean: clean
	@echo "[!] Removed $(NAME) [!]"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
