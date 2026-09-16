##
## EPITECH PROJECT, 2024
## 42sh
## File description:
## Makefile input
##

CFLAGS = -Wall -Wextra -I../../include

SRC = 	get_input.c\
		handle_sequences.c\
		manage_input.c\
		manage_input_struct.c\
		check_shortcut.c\
		autocompletion.c\

OBJ = $(SRC:.c=.o)

NAME = ../../libs/libinput.a

$(NAME): $(OBJ)
	@echo "[-] Compiling $(NAME) [-]"
	@ar rc $(NAME) $(OBJ) > /dev/null
	@echo "[V] Compilation done ! [V]"

all: $(NAME)

clean:
	@echo "[!] Removing object files [!]"
	rm -f $(OBJ)

fclean: clean
	@echo "[!] Removing $(NAME) [!]"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
