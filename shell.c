#include "shell.h"

/**
*main - execution point
*@argv: vectors
*@argc: vectors count
*Return: 0
*/

int main(__attribute__((unused))int argc, char *argv[])
{
	ShellData data;

	signal(SIGINT, sigint_handler);
	assign(&data, argv);
	program_integration(&data);
	free_shell_data(&data);
	if (data.exit_status < 0)
		return (255);
	return (data.exit_status);
}
