#include "shell.h"

/**
*print_help - prints out help information for the "help" shell
*Return: void
*/
void print_help(void)
{
	dprintf(STDOUT_FILENO, "help: help [-dms] [pattern ...]\n");
	dprintf(STDOUT_FILENO, "\tDisplay information about builtin commands.\n");
	dprintf(STDOUT_FILENO, "\tDisplays brief summaries of builtin commands.\n");
}

/**
*print_help_exit - prints out help information for the "exit" shell
*Return: void
*/
void print_help_exit(void)
{
	dprintf(STDOUT_FILENO, "exit: exit [n]\n Exit shell.\n");
	dprintf(STDOUT_FILENO, "Exits the shell with a status of N.");
	dprintf(STDOUT_FILENO, "If N is omitted, the exit ");
	dprintf(STDOUT_FILENO, "status is that of the last command executed.\n");
}

/**
*print_help_cd - prints out help information for the "cd" shell
*Return: void
*/
void print_help_cd(void)
{
	dprintf(STDOUT_FILENO, "cd: cd [-L|[-P [-e]] [-@]] [dir]\n");
	dprintf(STDOUT_FILENO, "\tChange the shell working directory.\n");
}

/**
*print_help_alias -prints out help information for the "alias" shell
*Return: void
*/
void print_help_alias(void)
{
	dprintf(STDOUT_FILENO, "alias: alias [-p] [name[=value]...]\n");
	dprintf(STDOUT_FILENO, "\tDefine or display aliases.\n");
}
/**
*general_help - ptints general help
*Return: void
*/
void general_help(void)
{
	dprintf(STDOUT_FILENO, "~$ bash, version 1.0(1)-release\n");
	dprintf(STDOUT_FILENO, "These commands are defined internally.");
	dprintf(STDOUT_FILENO, "Type 'help' to see the list.\n");
	dprintf(STDOUT_FILENO, "Type 'help name' to find out more")
	dprintf(STDOUT_FILENO, " about the function 'name'.\n\n");
	dprintf(STDOUT_FILENO, "alias: alias [name=['string']]\n");
	dprintf(STDOUT_FILENO, "cd: cd [-L|[-P [-e]] [-@]] [dir]\n");
	dprintf(STDOUT_FILENO, "exit: exit [n]\n");
	dprintf(STDOUT_FILENO, "env: env [option] [name=value] [command [args]]\n");
	dprintf(STDOUT_FILENO, "setenv: setenv [variable] [value]\n");
	dprintf(STDOUT_FILENO, "unsetenv: unsetenv [variable]\n");
}

