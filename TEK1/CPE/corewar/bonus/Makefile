##
## EPITECH PROJECT, 2024
## MiniShell1
## File description:
## Makefile
##

SRC		=	src/main.c						\
            src/help.c						\
            src/flags.c						\
            src/free.c						\
			src/init/init_arena.c			\
			src/init/init_champions.c		\
			src/init/init_vm.c				\
			src/parse_file.c				\
			src/init/init_positions.c		\
			src/store_instructions.c		\
			src/check_args.c				\
			src/corewar.c					\
			src/utilities.c					\
			src/op_tab.c					\
			src/instructions/live.c			\
			src/instructions/add.c			\
			src/instructions/sub.c			\
			src/instructions/zjmp.c			\
			src/instructions/aff.c			\
			src/instructions/and.c			\
			src/instructions/fork.c			\
			src/instructions/ld.c			\
			src/instructions/ldi.c			\
			src/instructions/lfork.c		\
			src/instructions/lld.c			\
			src/instructions/lldi.c			\
			src/instructions/or.c			\
			src/instructions/st.c			\
			src/instructions/sti.c			\
			src/instructions/xor.c			\
			src/csfml/create_function.c		\
			src/csfml/handle_event.c		\
			src/csfml/display.c				\
			src/csfml/utilities.c    		\
            src/csfml/buttons.c				\
			src/csfml/handle_menu.c


NAME	=	corewar

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude_csml -L. -lmy -Wall -Wextra

CSFMLFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(CSFMLFLAGS) > /dev/null
			@echo "Compilation done"

clean:
			@make -C lib/my clean > /dev/null
			@rm -f $(OBJ)
			@echo "Cleaning done"

fclean:		clean
			@make -C lib/my fclean > /dev/null
			@rm -f $(NAME)
			@echo "Full cleaning done."

re:			fclean all

debug:		$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(CSFMLFLAGS) -g
