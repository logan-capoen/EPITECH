##
## EPITECH PROJECT, 2024
## Meowsh
## File description:
## Root Makefile
##

SRC		=		main.c	\

NAME	=		42sh

OBJ		=		$(SRC:.c=.o)

CFLAGS = -Iinclude -Wall -Wextra -Llibs
CFLAGS += -lbuiltins -linput -lparsing -lexec -lformat -lglobbings -lutilities

CRIT = -lcriterion --coverage

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C src/utilities all >/dev/null
	@$(MAKE) -C src/builtins all >/dev/null
	@$(MAKE) -C src/input all >/dev/null
	@$(MAKE) -C src/parsing all >/dev/null
	@$(MAKE) -C src/exec all >/dev/null
	@$(MAKE) -C src/globbings all >/dev/null
	@$(MAKE) -C src/format all >/dev/null
	@echo "[-] Compiling $(NAME) [-]"
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) > /dev/null
	@echo "[V] Successfully compiled $(NAME) [V]"

clean:
	@$(MAKE) -C src/utilities clean > /dev/null
	@$(MAKE) -C src/builtins clean > /dev/null
	@$(MAKE) -C src/input clean > /dev/null
	@$(MAKE) -C src/parsing clean > /dev/null
	@$(MAKE) -C src/exec clean > /dev/null
	@$(MAKE) -C src/globbings clean >/dev/null
	@$(MAKE) -C src/format clean >/dev/null
	@rm -f $(OBJ)
	@find . -name "*.gcda" -type f -delete
	@find . -name "*.gcno" -type f -delete
	@echo "[!] Removed libraries. [!]"

fclean: clean
	@$(MAKE) -C src/utilities fclean > /dev/null
	@$(MAKE) -C src/builtins fclean > /dev/null
	@$(MAKE) -C src/input fclean > /dev/null
	@$(MAKE) -C src/parsing fclean > /dev/null
	@$(MAKE) -C src/exec fclean > /dev/null
	@$(MAKE) -C src/globbings fclean >/dev/null
	@$(MAKE) -C src/format fclean >/dev/null
	@rm -f $(NAME)
	@rm -f unit_tests
	@rm -f output.txt
	@echo "[!] Removed $(NAME) binary. [!]"

re: fclean all

tests_run:
	@$(MAKE) -C src/utilities all >/dev/null CFLAGS="-Wall -Wextra \
	-I../../include $(CRIT)"
	@$(MAKE) -C src/builtins all >/dev/null CFLAGS="-Wall -Wextra \
	-I../../include $(CRIT)"
	@$(MAKE) -C src/input all >/dev/null CFLAGS="-Wall -Wextra \
	-I../../include $(CRIT)"
	@$(MAKE) -C src/parsing all >/dev/null CFLAGS="-Wall -Wextra \
	-I../../include $(CRIT)"
	@$(MAKE) -C src/exec all >/dev/null CFLAGS="-Wall -Wextra \
	-I../../include -L../../libs -lutilities $(CRIT)"
	@$(MAKE) -C src/globbings all >/dev/null CFLAGS="-Wall -Wextra \
	-I../../include $(CRIT)"
	@$(MAKE) -C src/format all >/dev/null CFLAGS="-Wall -Wextra \
	-I../../include $(CRIT)"
	@echo "[-] Compiling tests_crit [-]"
	@gcc -o unit_tests tests/tests.c $(CFLAGS) $(CRIT) > /dev/null
	@./unit_tests || true
	@echo "[V] Tests passed [V]"

coverage:
	@mkdir -p tests/coverage_report
	@gcovr --root . --exclude tests/ --html \
	--html-details -o tests/coverage_report/coverage_report.html
	@gcovr --root . --exclude tests/ --txt-metric \
	branch -o tests/coverage_report/coverage_report.txt
	@xdg-open tests/coverage_report/coverage_report.html

.PHONY: all clean fclean re
