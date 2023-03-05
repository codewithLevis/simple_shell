#include "shell.h"

/**
*sigint_handler - handling SIGINT signal
*@signum: signal number on CTRL C
*Return: void
*/

void sigint_handler(__attribute__((unused))int signum)
{
	dprintf(STDOUT_FILENO, "\n~$ ");
}
