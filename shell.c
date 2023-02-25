#include "shell.h"

/**
*main - execution and coordination point
*@argc: number of vectors
*@argv: vectors
*Return: 0
*/

int main (__attribute__((unused)) int argc, char **argv)
{
	data_shell datash;

	signal(SIGINT, get_sigint);
	set_data(&datash, argv);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
