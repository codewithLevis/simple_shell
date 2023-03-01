#include "shell.h"

/**
*execute - execute built-in commands or
*external programs based on the given command line arguments
*@ptr: pointer to shell struct
*Return: 1
*/
int execute(ShellData *ptr)
{
	int (*builtin)(ShellData *ptr);

	if ((*ptr).parsed_input_args[0] == NULL)
	{
	/*Empty command line*/
		return (1);
	}

	/*Check if command is a builtin*/
	builtin = find_builtin_func((*ptr).parsed_input_args[0]);

	if (find_builtin_func != NULL)
		return (find_builtin_func(ptr));

	// Execute external command
	return execute_external_command(datash);
}
