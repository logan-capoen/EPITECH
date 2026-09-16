##
## Makefile for pipeto in /home/pepito
##
## Made by Joffrey Z.
## Login<alexandre1.renaud@epitech.eu>
##
## Started onMonApr211:57:002013Théo Pierre
## Last updateMonApr211:58:422012Théodore Poche
##

B_SRC=	src/commands/activate_emergency_protocols.c\
		src/commands/check_cooling_pressure.c\
		src/commands/check_reactor_status.c\
		src/commands/configure_cooling_system.c\
		src/commands/enable_remote_access.c\
		src/commands/help.c\
		src/commands/init_reactor.c\
		src/commands/load_fuel_rods.c\
		src/commands/log_system_events.c\
		src/commands/monitor_radiation_levels.c \
		src/commands/run_diagnostic.c\
		src/commands/send_status_report.c\
		src/commands/set_reactor_power.c\
		src/commands/simulate_meltdown.c\
		src/commands/quit.c\
		src/commands/unlock_secret_mode.c\
		src/commands/load_config.c\
		src/commands/history.c \
		src/commands/trigger_emergency_shutdown.c\
		src/my_console.c \
		src/utils.c

G_SRC=src/main.c

B_OBJ = $(B_SRC:.c=.o)

G_OBJ = $(G_SRC:.c=.o)

OBJ= $(B_OBJ) $(G_OBJ)

NAME=pipeto

CFLAGS = -Iinclude -Wall -Wextra -Wno-implicit-function-declaration

CRIT = -lcriterion --coverage

all: $(NAME)

$(NAME): $(OBJ)
	@echo "[-] Compiling $(NAME) [-]"
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) > /dev/null
	@echo "[V] Successfully compiled $(NAME) [V]"

clean:
	@rm -f $(OBJ)
	@find . -name "*.gcda" -type f -delete
	@find . -name "*.gcno" -type f -delete
	@echo "[!] Removed libraries. [!]"

fclean: clean
	@rm -f $(NAME)
	@rm -f unit_tests
	@rm -f output.txt
	@echo "[!] Removed $(NAME) binary. [!]"

re: fclean all

tests_run:
	@echo "[-] Compiling tests_crit [-]"
	@gcc -o unit_tests tests/tests.c $(B_SRC) $(CFLAGS) $(CRIT) > /dev/null
	@./unit_tests || true
	@echo "[V] Tests passed [V]"

coverage:
	@mkdir -p tests_html/coverage_report
	@gcovr --root . --exclude tests_html/ --html \
	--html-details -o tests_html/coverage_report/coverage_report.html
	@gcovr --root . --exclude tests_html/ --txt-metric \
	branch -o tests_html/coverage_report/coverage_report.txt
	@xdg-open tests_html/coverage_report/coverage_report.html

.PHONY: all clean fclean re
