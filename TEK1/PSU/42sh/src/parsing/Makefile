##
## EPITECH PROJECT, 2024
## B-PSU-200-LIL-2-1-42sh-mato.urbanac
## File description:
## Makefile
##

CFLAGS += -Wall -Wextra -I../../include

SRC =   is_command_valid/is_command_valid.c \
        is_command_valid/check_matched.c \
        is_command_valid/check_pipes.c \
		is_command_valid/check_double_and.c \
		is_command_valid/check_semicolons.c \
        main_parsing/nesting_handling.c \
        main_parsing/parser.c \
        command_handling/separators.c \
        command_handling/simple_command.c \
        command_handling/open_fd_redirections.c \

OBJ = $(SRC:.c=.o)

NAME = ../../libs/libparsing.a

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
