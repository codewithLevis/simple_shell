#include "shell.h"


/**
*prompt - prints prompt message
*Return: void
*/
void prompt(void)
{
	dprintf(STDIN_FILENO, "~$ ");
}

/**
*read_input - reads user input
*@ctrl_d: cheking fo retur value of getline
*Return: read user input
*/
char *read_input(int *ctrl_d)
{
	char *input = NULL;
	size_t buf = 0;

	*ctrl_d = getline(&input, &buf, stdin);

	return (input);
}

/**
*remove_comment - removing any text following a # character in the input string
*@input: user input
*Return: comment with no comments
*check if the sign is part of word if so it leaves
*/

char *remove_comment(char *input)
{
	int i = 0, comment_start = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}
			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
			{
				comment_start = i;
			}
		}
		i++;
	}
	if (comment_start != 0)
	{
		input = _realloc(input, i, comment_start + 1);
		input[comment_start] = '\0';
	}
	return (input);
}


/**
*program_integration - repeatedly prompts the user for input, reads the input, and executes it
*@ptr: pointer to the ShellData struct
*Return: void
*/

void program_integration(ShellData *ptr)
{
	int flag = 1, ctrl_d;
	char *input;

	while(flag == 1)
	{
		if (isatty(STDIN_FILENO))
			prompt();

		input = read_input(&ctrl_d);
		if (ctrl_d != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;
			if (find_syntax_error(ptr, input) == 1)
			{
				(*ptr).exit_status = 2;
				free(input);
				continue;
			}
			input = expand_variables(input, ptr);
			flag = execute_commands(ptr, input);
			(*ptr).command_counter += 1;
			free(input);
		}
		/*else
		{
			flag = 0;
			free(input);
		}*/
	}
}
