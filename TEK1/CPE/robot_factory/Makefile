##
## EPITECH PROJECT, 2024
## MiniShell1
## File description:
## Makefile
##

SRC		=	src/main.c						\
			src/open.c						\
			src/help.c						\
			src/header/header_compile.c 	\
			src/header/header_check.c 		\
			src/body/body_check.c			\
			src/body/body_compile.c			\
			src/utilities.c					\
			src/instructions/add.c			\
			src/instructions/aff.c			\
			src/instructions/and.c			\
			src/instructions/fork.c			\
			src/instructions/ld.c 			\
			src/instructions/ldi.c 			\
			src/instructions/lfork.c 		\
			src/instructions/live.c 		\
			src/instructions/lld.c 			\
			src/instructions/lldi.c 		\
			src/instructions/or.c 			\
			src/instructions/st.c 			\
			src/instructions/sti.c 			\
			src/instructions/sub.c 			\
			src/instructions/xor.c 			\
			src/instructions/zjmp.c			\
			src/body/body_bytes.c			\
			src/body/labels.c				\
			src/body/body_struct.c

NAME	=	asm

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lmy -Wall -Wextra

all:		libmy.a		$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) > /dev/null
			@echo "Compilation done"

clean:
			@make -C lib/my clean > /dev/null
			@rm -f $(OBJ)
			@echo "Cleaning done"

fclean:		clean
			@make -C lib/my fclean > /dev/null
			@rm -f $(NAME)
			@rm -f libmy.a
			@echo "Full cleaning done."

re:			fclean all

libmy.a:
			@echo "Compiling lib"
			@make -C lib/my > /dev/null
			@cp lib/my/libmy.a .

debug:		libmy.a		$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) -g
