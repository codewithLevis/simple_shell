#include "shell.h"

/**
*main - execution point
*@argv: vectors
*@argc: vectors count
*Return: 0
*/

int main(__attribute__((unused))int argc, char *argv[])
{
	ShellData data, *ptr_data;
	
	ptr_data = &data;
	signal(SIGINT, sigint_handler);
	assign(ptr_data, argv);
	program_integration(ptr_data);
	free_shell_data(ptr_data);
	if ((*ptr_data).exit_status < 0)
		return (255);
	return ((*ptr_data).exit_status);
}
