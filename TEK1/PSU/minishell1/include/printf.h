/*
** EPITECH PROJECT, 2024
** printf header
** File description:
** header with struct def
*/

#ifndef PRINTF
    #define PRINTF
    #include <stdarg.h>

typedef struct specifiers {
    char *flags;
    int width;
    int precision;
    char arg_type;
} specifiers_t;

typedef struct flag_struct {
    char flag;
    char *(*function)(char *);
} flag_struct_t;

typedef struct arg_type {
    char letter;
    char *(*function)(va_list);
} arg_type_t;

int my_printf(char *format, ...);
specifiers_t tab_spec(char *format, int *i);
char *handle_zero_i_d(specifiers_t spec, char *buff_arg_type);
int rounded(specifiers_t *spec, char *buff_arg_type);
char *flags(specifiers_t spec, char *buff_width);
char *width(specifiers_t spec, char *buff_precision);
char *arg_type(specifiers_t spec, va_list valist);
char *precision(specifiers_t spec, char *buff_arg_type);
int int_to_str(int num, char *buff);
int my_len_int(int num);
int print_arg(char *format, va_list valist, int *i, int *len);
int is_flag(char chara);
int flag_len(char *format);
char *put_flags(char *format, int *i, char *flags);
int put_width(char *format, int *i);
int put_precision(char *format, int *i);
char put_arg_type(char *format, int *i);
char *i_d_type(va_list valist);
char *o_type(va_list valist);
char *u_type(va_list valist);
char *x_type(va_list valist);
char *x_uppercase_type(va_list valist);
char *e_type(va_list valist);
char *e_uppercase_type(va_list valist);
char *f_type(va_list valist);
char *g_type(va_list valist);
char *g_uppercase_type(va_list valist);
char *a_type(va_list valist);
char *a_uppercase_type(va_list valist);
char *c_type(va_list valist);
char *s_type(va_list valist);
char *p_type(va_list valist);
char *n_type(va_list valist);
char *m_type(va_list valist);
char *pourcent_type(va_list valist);
char *dash_flag(char *buffer);
char *zero_flag(char *buffer);
char *space_flag(char *buffer);
char *plus_flag(char *buffer);
char *sharp_flag(char *buffer);
int index_flag(char chara, specifiers_t spec);
char *exe_ptr_on_fct(char c, char *buff_width);
int special_flags_case(specifiers_t *spec);
int sort_flags(specifiers_t *spec);
char *handle_zero_f(specifiers_t spec, char *buff_arg_type);
#endif
