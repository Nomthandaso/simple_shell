#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell_loop.c */
int hsh(info_t *info, char **argv);
int get_builtin(info_t *info);
void find_cmd(info_t *info);
void my_fork(info_t *info);

/* my_parser.c */
int my_cmd(info_t *info, char *path);
char *duplicate_chars(char *str_pth, int strt, int stop);
char *find_pth(info_t *info, char *path_str, char *cmd);

/* my_errors.c */
void my_eputs(char *str);
int _eputchar(char d);
int my_putfd(char d, int fd);
int my_putsfd(char *str, int fd);

/* my_string.c */
int my_strlen(char *str);
int my_strcmp(char *str1, char *str2);
char *starts_with(const char *yikes, const char *trollz);
char *my_strcat(char *dest, char *src);

/* my_string1.c */
char *my_strcpy(char *dest, char *src);
char *my_strdup(const char *str);
void my_puts(char *str);
int _putchar(char c);

/* my_exits.c */
char *my_strncpy(char *dest, char *src, int m);
char *my_strncat(char *dest, char *src, int n);
char *my_strchr(char *str, char car);

/* my_tokenizer.c */
char **tokenize_str(char *str, char d);
char **split_str(char *str, char *d);

/* my_realloc.c */
char *my_memset(char *ptr, char byte, unsigned int n);
void free_me(char **pptr);
void *my_realloc(void *ptr, unsigned int old_s, unsigned int new_s);

/* my_memory.c */
int fr_ee(void **pointer);

/* my_atoi.c */
int my_interactive(info_t *info);
int my_delim(char m, char *delim);
int alpha_char(int m);
int _atoi(char *d);

/* my_errors1.c */
int _erratoi(char *t);
void print_error(info_t *info, char *str);
int print_dec(int input, int fd);
char *conv_number(long int num, int base, int flags);
void rm_comments(char *buff);

/* my_builtin.c */
int my_exit(info_t *info);
int my_cd(info_t *info);
int my_help(info_t *info);

/* my_builtin1.c */
int my_history(info_t *info);
int my_alias(info_t *info);
int print_a(list_t *node);
int set_alias(info_t *info, char *str);
int _alias(info_t *info, char *str);

/* my_getline.c */
ssize_t get_input(info_t *info);
int my_getline(info_t *info, char **ptr, size_t *len);
void sigintHandler(__attribute__((unused)) int sig_num);
ssize_t input_buffer(info_t *info, char **buffer, size_t *length);
ssize_t read_buffer(info_t *info, char *buffer, size_t *n);

/* my_getinfo.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int pills);

/* my_environ.c */
char *my_getenv(info_t *info, const char *n);
int my_env(info_t *info);
int my_setenv(info_t *info);
int my_unsetenv(info_t *info);
int pop_env_list(info_t *info);

/* my_history.c */
char *get_history_file(info_t *info);
int wrt_history(info_t *info);
int rd_history(info_t *info);
int build_history_list(info_t *info, char *buffer, int line_count);
int renum_history(info_t *info);

/* my_lists.c */
list_t *add_nd(list_t **hd, const char *str, int num);
list_t *add_nd_end(list_t **hd, const char *str, int num);
size_t my_list(const list_t *k);
int del_nd_at_index(list_t **hd, unsigned int index);
void free_list(list_t **head_pointer);

/* my_lists1.c */
size_t list_length(const list_t *k);
char **list_strings(list_t *hd);
size_t print_list(const list_t *k);
list_t *nd_starts_with(list_t *nd, char *prefix, char d);
ssize_t get_nd_index(list_t *hd, list_t *nd);

/* my_vars.c */
int my_chain(info_t *info, char *buffer, size_t *q);
void check_chain(info_t *info, char *b, size_t *q, size_t i, size_t l);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_str(char **old, char *not_new);

/* my_getenv.c */
int _setenv(info_t *info, char *vari, char *val);
int _unsetenv(info_t *info, char *vari);
char **get_environ(info_t *info);

#endif
