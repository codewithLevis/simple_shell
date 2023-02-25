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

#endif /*SHELL_H*/
