/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** op
*/

#ifndef _OP_H_
    #include "my.h"
    #define _OP_H_
    #define MEM_SIZE (6 * 1024)
    #define IDX_MOD 512 /* modulo of the index < */
    #define MAX_ARGS_NUMBER 4 /* this may not be changed 2^*IND_SIZE */
    #define COMMENT_CHAR '#'
    #define LABEL_CHAR ':'
    #define DIRECT_CHAR '%'
    #define SEPARATOR_CHAR ','
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
    #define NAME_CMD_STRING ".name"
    #define COMMENT_CMD_STRING ".comment"
    /*
    ** regs
    */
    #define REG_NUMBER 16 /* r1 <--> rx */
    #define T_REG 1 /* register */
    #define T_DIR 2 /* direct  (ld  #1,r1  put 1 into r1) */
    #define T_IND 4
    //indirect always relative (ld 1,r1 put what's in
    //the address (1+pc) into r1 (4 bytes ))

    #define T_LAB 8 /* LABEL */
    /*
    ** size (in bytes)
    */
    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE
    /*
    ** header
    */
    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3
    /*
    ** live
    */
    #define CYCLE_TO_DIE 1536 /* number of cycle before beig declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40

    #define BIGINT_SIZE 12

/*
**
*/
typedef char args_type_t;

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
    char *comment;
} op_t;


typedef struct header_s {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef struct label_s {
    char *name;
    int position;
    struct label_s *next;
} label_t;

typedef struct args_s {
    char *value;
    int nb_bytes;
} args_t;

typedef struct body_s {
    int instruction;
    char codingbyte;
    args_t arguments[MAX_ARGS_NUMBER];
    struct body_s *next;
} body_t;

//OPEN
int open_file(int ac, char **av);
int create_cor(char **av);
char *create_buffer(int ac, char **av);

//HEADER
char **check_header(char **arr);
int compile_header(char **arr, char **av, int size);
int check_wrong_quotes(char *buff);
char *remove_comments(char *buff);

//BODY
int check_instruction(char *str);
int get_size(char *path);
int check_label(char *str);
char **extract_body(char **arr);
int search_type(char *arg, char *instruction);
int count_awaited_args(char **body);
int parsing_body(char **body, label_t **labels, body_t **instructions);
void add_argument(body_t **instructions, char *value, int nb_bytes, int i);
int add_instruction(body_t **instructions, int instruction);
void create_coding_byte(body_t *head);
int handle_body(char **arr, label_t **labels, body_t **instructions,
    char ***extracted_body);
void compile_body(body_t *head, int fd_cor);
int compare_args_number(char **body);
int check_coding_byte(int instruction);

//LABEL
int check_label(char *str);
int add_label(label_t **head, char *name, int position);
char *check_label_params(char *params);
int find_value_labels(label_t *head, char *label_name, int curr_pos);

//UTIILITIES
int check_help(int argc, char **argv);
unsigned int reverse_bytes(unsigned int num, int size);
void our_rev_list(body_t **begin);
char *int_to_str(int num);
void free_double_arr(char **arr);

#endif
