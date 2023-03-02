#include "shell.h"

/**
*get_shell_command_name - verifies string argument
*@arg: string argument
*Return: the corresponding shell command value
*/
CommandName get_shell_command_name(char *arg)
{
	if (_strcmp(arg, "setenv") == 0)
	{
		return (COMMAND_SETENV);
	}
	else if (_strcmp(arg, "env") == 0)
	{
		return (COMMAND_ENV);
	}
	else if (_strcmp(arg, "unsetenv") == 0)
	{
		return (COMMAND_UNSETENV);
	}
	else if (_strcmp(arg, "help") == 0)
	{
		return (COMMAND_HELP);
	}
	else if (_strcmp(arg, "exit") == 0)
	{
		return (COMMAND_EXIT);
	}
	else if (_strcmp(arg, "cd") == 0)
	{
		return (COMMAND_CD);
	}
	else if (_strcmp(arg, "alias") == 0)
	{
		return (COMMAND_ALIAS);
	}
	else
	{
		return (-1);
	}
}

/** 
*print_help_setenv - prints out help information for the "setenv" shell
*Return: void
*/
void print_help_setenv(void)
{
	dprintf(STDOUT_FILENO, "setenv: setenv (const char *name, const char *value, int replace)\n\t");
	dprintf(STDOUT_FILENO, "Add a new definition to the environment\n");
}

/**
*print_help_env - prints out help information for the "env" shell
*Return: void
*/
void print_help_env(void)
{
	dprintf(STDOUT_FILENO, "env: env [option] [name=value] [command [args]]\n\t");
	dprintf(STDOUT_FILENO, "Print the environment of the shell.\n");
}

/**
*print_help_unsetenv - prints out help information for the "unsetenv" shell
*Return: void
*/
void print_help_unsetenv(void)
{
	dprintf(STDOUT_FILENO, "unsetenv: unsetenv (const char *name)\n\t");
	dprintf(STDOUT_FILENO, "Remove an entry completely from the environment\n");
}

/**
*print_shell_help - prints out help information for
*a specific shell command or general shell usage.
*@ptr: pointer to a ShellData 
*Return: 1 upon completion.
*/
int print_shell_help(ShellData *ptr)
{
	char *arg = (*ptr).parsed_input_args[1];
	int status = 0;

	if (arg == NULL)
	{
        	general_help();
	}

	else
	{
		switch (get_shell_command_name(arg))
		{
			case COMMAND_SETENV:
				print_help_setenv();
				break;
			case COMMAND_ENV:
				print_help_setenv();
				break;
			 case COMMAND_UNSETENV:
				print_help_unsetenv();
				break;
			 case COMMAND_HELP:
				print_help();
				break;
			case COMMAND_EXIT:
				print_help_exit();
				break;
			case COMMAND_CD:
				print_help_cd();
				break;
			case COMMAND_ALIAS:
				print_help_alias();
				break;
			default:
				dprintf(STDERR_FILENO, "%s", (*ptr).parsed_input_args[0]);
				status = 1;
				break;
		}
	}

	(*ptr).exit_status = status;
	return (1);
}
