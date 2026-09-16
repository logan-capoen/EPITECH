##
## EPITECH PROJECT, 2025
## 42sh
## File description:
## Makefile for utilities
##

CFLAGS += -Wall -Wextra -I../../include

SRC		=	str_alphanum.c\
			manage_char_array.c\
			free_shell.c\
			init_shell.c\
        	my_str_to_word_array.c\
			strjoin.c\
			int_to_str.c\

OBJ = $(SRC:.c=.o)

NAME = ../../libs/libutilities.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "[-] Compiling $(NAME) [-]"
	@ar rc $(NAME) $(OBJ) > /dev/null
	@echo "[V] Compilation done ! [V]"

clean:
	@echo "[-] Removing object files [-]"
	$(RM) $(OBJ)

fclean: clean
	@echo "[-] Removing $(NAME) [-]"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
