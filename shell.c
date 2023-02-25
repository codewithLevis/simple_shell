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
}
	
	
	
