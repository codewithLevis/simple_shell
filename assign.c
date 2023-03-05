#include "shell.h"

/**
*assign - assign value to every member of ShellData
*@shell_data: pointer to shell data variable type to fill
*its memory
*@command_line_args: vectors
*Return: void
*/

void assign(ShellData *shell_data, char **command_line_args)
{
	unsigned int i;

	shell_data->command_counter = 1;
	shell_data->exit_status = 0;
	shell_data->command_line_args = command_line_args;
	shell_data->user_input = NULL;
	shell_data->parsed_input_args = NULL;
	shell_data->process_id = _itoa(getpid());

	for (i = 0; environ[i]; i++)
		;

	shell_data->environment_vars = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
		shell_data->environment_vars[i] = _strdup(environ[i]);

	shell_data->environment_vars[i] = NULL;
}
