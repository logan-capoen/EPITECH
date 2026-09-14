/*
** EPITECH PROJECT, 2024
** mytop.h
** File description:
** mytop header
*/

#ifndef MYTOP
    #define MYTOP
    #include <stdlib.h>
    #include <ncurses.h>
    #include "printf.h"
    #include <unistd.h>
    #include <time.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include "my.h"
    #include <pwd.h>
    #include <string.h>
    #include <fcntl.h>
typedef struct linked_list {
    char *pid;
    char *username;
    char *pr;
    char *ni;
    char *virt;
    unsigned long time;
    char state;
    struct linked_list *next;
} proc_t;
typedef struct mib {
    double total;
    double free;
    double used;
    double avail;
}mib_t;
typedef struct cpu_time {
    unsigned long us;
    unsigned long sy;
    unsigned long ni;
    unsigned long id;
    unsigned long wa;
    unsigned long hi;
    unsigned long si;
    unsigned long st;
} cpu_time_t;
typedef struct cpu {
    double us;
    double sy;
    double ni;
    double id;
    double wa;
    double hi;
    double si;
    double st;
} cpu_t;
int my_top(int delay, int end, char *user);
struct tm *get_time(void);
proc_t *get_procs(void);
int display_procs(proc_t *procs, int line, char *user);
char *get_username(int pid);
char **get_stat(int pid);
int *get_states(proc_t *procs);
int display_header(cpu_time_t *prev);
mib_t *get_mem_info(void);
mib_t *get_swap_info(void);
unsigned long get_res(int pid);
cpu_t *get_cpu_pourcentage(cpu_time_t *p);
int read_cpu_times(cpu_time_t *cpu);
char *get_command_name(int pid);
#endif
