#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>

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

/*string1.c*/
int _strlen(const char *s);
int get_int_length(int num);
char *_itoa(int num);
char *_strdup(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);

/**
*struct Builtin - structure for built-in commands
*@name: name of the built-in command (e.g. cd, exit, env)
*@func: function pointer to the corresponding built-in function
*/
typedef struct Builtin
{
	char *name;
	int (*func)(data_shell *datash);
} Builtin;

/**
*struct VarNode_t - represents a node in a singly linked list that stores variables
*@len_var: length of the variable
*@value: value of the variable
*@len_val: length of the value
*@next: pointer to the next node in the list
*Description: This struct defines a node in a singly linked list used to store variables.
*The len_var field holds the length of the variable, the val field holds the value of the variable,
*the len_val field holds the length of the value, and the next field points to the next node in the list.
*/
typedef struct VarNode_t
{
	int len_var;
	char *value;
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
} VarNode_t;

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

#endif /*SHELL_H*/
