#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

void sigint_handler(int signum);

/**
*typedef struct ShellData - set of variables commonly used in a shell program
*@user_input: pointer to user's input, typically read from command line
*@command_counter: number of commands executed by the shell program
*@command_line_args: pointer to command-line arguments passed to the program
*@int exit_status: exit status of last executed command
*@parsed_input_args: pointer to individual arguments parsed from user's input
*@process_id:  pointer to process ID (PID) of the shell program
*@environment_vars: pointer to environment variables passed to the shell program
*/
typedef struct
{
	int command_counter;
	int exit_status;
	char **command_line_args;
	char *user_input;
	char **parsed_input_args;
	char **environment_vars;
	char *process_id;
} ShellData;

/*assign.c*/
void assign(ShellData *shell_data, char **command_line_args);

/**
*struct Builtin - structure for built-in commands
*@name: name of the built-in command (e.g. cd, exit, env)
*@func: function pointer to the corresponding built-in function
*/
typedef struct Builtin
{
	char *name;
	int (*func)(ShellData *ptr);
} Builtin;

/**
*struct VarNode_t - represents a node in a singly linked list that stores variables
*@len_var: length of the variable
*@val: value of the variable
*@len_val: length of the value
*@next: pointer to the next node in the list
*Description: This struct defines a node in a singly linked list used to store variables.
*The len_var field holds the length of the variable, the val field holds the value of the variable,
*the len_val field holds the length of the value, and the next field points to the next node in the list.
*/
typedef struct VarNode_t
{
	int len_var;
	char *val;
	int len_val;
	struct VarNode_t *next;
} VarNode_t;

/**
*struct SeparatorNode - single linked list
*@symbol: ; | &
*@next: pointer to next node
*Description: single linked list to store separators
*stores able to separate the commands entered by the user
*into different parts to be executed separately
*/
typedef struct SeparatorNode
{
	char symbol;
	struct SeparatorNode *next;
} SeparatorNode;

/**
*struct CommandLineNode - singly linked list for command lines
*@command: the command line string
*@next: pointer to the next node in the list
*A singly linked list structure used to store command lines.
*/
typedef struct CommandLineNode
{
	char *command;
	struct CommandLineNode *next;
} CommandLineNode;

/*builtins.c*/
int (*find_builtin_func(char *cmd))(ShellData *);
int _env(ShellData *ptr);
int exit_handler(ShellData *ptr);

/*cd.c*/
void cd_parent_dir(ShellData *ptr);
void cd_change_dir(ShellData *ptr);
void cd_prev_dir(ShellData *ptr);
void cd_home_dir(ShellData *ptr);
int change_directory(ShellData *datash);

/*dollar_val.c*/
void search_env_var(VarNode_t **start, char *in, ShellData *ptr);
int parse_vars(VarNode_t **head, char *input, char *status, ShellData *ptr);
char *expansion(VarNode_t **start, const char *in, char *new, int new_len);
char *expand_variables(char *input, ShellData *ptr);

/*env_reset.c*/
char *_create_env_var(char *name, char *value);
int _setenv(ShellData *ptr);
int _unsetenv(ShellData *ptr);
char *_getenv(const char *value, char **env);
void _set2env(char *key, char *value, ShellData *ptr);

/*error.c*/
int check_first_character(char *input, char *offset);
void print_shell_error(ShellData *ptr_data, char *input, int idx, int t_msg);
int duplicates(char *input, int i);
int check_separator(char *input, int i, char offset);
int find_syntax_error(ShellData *ptr_data, char *input);

/*error2.c*/
int handle_error(ShellData *prt, int error_no);
char *env_err(ShellData *ptr);
char *path_126_err(ShellData *ptr);
char *not_found_err(ShellData *ptr);
char *exit_shell_err(ShellData *ptr);

/*error3.c*/
char *generate_cd_err(ShellData *ptr);
int search_cmd_error(char *dir, ShellData *ptr);

/*execute.c*/
char *encoder(char *input, int encode);
void parse_input(char *input, SeparatorNode **head, CommandLineNode **start);
void *get_next(CommandLineNode *head, SeparatorNode *start, ShellData *data);
int execute_commands(ShellData *ptr, char *input);

/*final.c*/
int is_command_executable(char *command, ShellData *ptr);
int is_path_segment(char *path, int *index);
char *get_path(char *cmd, char **envp);
int execute_cmd(char **args, char **environ_vars, ShellData *ptr);
int execute(ShellData *ptr);

/*help.c*/
char *get_shell_command_name(char *arg);
void print_help_setenv(void);
void print_help_env(void);
void print_help_unsetenv(void);
int print_shell_help(ShellData *ptr);

/*help2.c*/
void print_help(void);
void print_help_exit(void);
void print_help_cd(void);
void print_help_alias(void);
void general_help(void);

/*node_handlers.c*/
VarNode_t *add_node(VarNode_t **start, int len_var, char *val, int len_val);
void free_VarNode_t(VarNode_t **start);
CommandLineNode *add_CommandLineNode(CommandLineNode **start, char *command);
SeparatorNode *add_SeparatorNode(SeparatorNode **head, char symbol);

/*node_handlers2.c*/
void free_SeparatorNode_list(SeparatorNode **head);
void free_CommandLineNode_list(CommandLineNode **start);
void free_shell_data(ShellData *ptr);

/*program.c*/
void prompt(void);
char *read_input(int *ctrl_d);
char *remove_comment(char *input);
void program_integration(ShellData *ptr);

/*string1.c*/
int _strlen(const char *s);
int get_int_length(int num);
char *_itoa(int num);
char *_strdup(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);

/*string2.c*/
char *_strncpy(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char *my_strtok(char *str, const char *delim);
char *_strndup(char *str, int i);
char **_realloc_double_ptr(char **old_ptr, unsigned int old_bytes, unsigned int new_bytes);

/*string3.c*/
int _isdigit(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
int _atoi(const char* str);

/*string4.c*/
void _strrev(char *str);

/*tokenize.c*/
char **my_reallocate(char **ptr_arr, unsigned int old_len, unsigned int new_len);
char **tokenize(char *input, const char *delim);

#endif /*SHELL_H*/
