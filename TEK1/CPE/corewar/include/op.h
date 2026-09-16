/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** op
*/

#ifndef _OP_H_
    #include "my.h"
    #include <stdbool.h>
    #include <ctype.h>
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

    #define MAX_CHAMPIONS 4
    #define MAX_ARGS 4

typedef struct proc_s {
    int pc;
    int carry;
    unsigned int wait;
    struct proc_s *next;
} proc_t;

typedef struct champion_s {
    int registers[REG_NUMBER];
    int id;
    int position;
    char *name;
    char *filename;
    int len;
    proc_t *procs;
} champion_t;

typedef struct {
    int offset;
    int arg_index;
    int arg_type;
    int *arg_type_array;
    int nb_args;
} args_t;

typedef struct arena_s {
    unsigned char *vm;
    bool live_signals[MAX_CHAMPIONS];
    bool alive_champions[MAX_CHAMPIONS];
    int dump;
    champion_t *champions[MAX_CHAMPIONS];
    int nb_champions;
    args_t *args;
    int nb_live_signal;
} arena_t;

typedef struct {
    unsigned int dump;
    unsigned int n;
    unsigned int a;
    char *prog_name;
} flags_t;

////////////// Help //////////////

int check_help(int argc, char **argv);
void display_help(void);

//////////////////////////////////

////////////// Flag //////////////

int parse_flag(arena_t *arena, int argc, char **argv);

//////////////////////////////////

///////// Initialization /////////

arena_t *init_arena(void);
void free_arena(arena_t *arena);
void init_champions(arena_t *arena);
unsigned char *init_vm(void);
void store_positions(arena_t *arena);
void init_alive_champions(arena_t *arena);
int get_names(arena_t *arena);
int store_instructions(arena_t *arena);

//////////////////////////////////

//////////// Corewar ///////////

int check_coding_byte(unsigned char instruction);
int launch_corewar(arena_t *arena);
int check_instruction(unsigned char byte);
int check_args(arena_t *arena, int position);
unsigned char *extract_instructions(champion_t *champion);
int get_wait_time(int index);

///////////////////////////////

//////////// Utilities ///////////

void reset_array(int *arr);
int check_instruction(unsigned char byte);
int check_coding_byte(unsigned char instruction);
int get_param(champion_t *champion, arena_t *arena,
    int arg_type, int position);
void create_node(champion_t *champion, int position);

//////////////////////////////////

#endif
