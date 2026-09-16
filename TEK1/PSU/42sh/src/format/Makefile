##
## EPITECH PROJECT, 2025
## 42sh
## File description:
## Makefile for formating
##

CFLAGS += -Wall -Wextra -I../../include

SRC		=	format.c\
			put_spaces.c\
			check_exception.c\

OBJ = $(SRC:.c=.o)

NAME = ../../libs/libformat.a

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
