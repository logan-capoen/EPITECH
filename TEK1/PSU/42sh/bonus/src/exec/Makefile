##
## EPITECH PROJECT, 2024
## 42sh
## File description:
## Makefile
##

CFLAGS += -Wall -Wextra -I../../include -L../../libs -lutilities

SRC =	check_signal.c\
        exec_cmd.c\
		get_cmd_path.c\
		get_cmd_type.c\
		manage_exec_data.c\

OBJ = $(SRC:.c=.o)

NAME = ../../libs/libexec.a

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
