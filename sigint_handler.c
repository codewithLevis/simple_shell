#include "shell.h"

/**
*sigint_handler - handling SIGINT signal
*@signum: signal number on CTRL C
*Return: void
*/

void sigint_handler(int signum)
{
	dprintf(STDOUT_FILENO, "\nShell interrupted on signal %d (SIGINT).\n~$ ", signum);
}
