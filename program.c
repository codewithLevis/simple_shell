#include "shell.h"


/**
*prompt - prints prompt message
*Return: void
*/
void prompt(void)
{
	dprintf(STDIN_FILENO, "~$ ");
}
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}
	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}
	return (in);
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

	if (input[*ctrl_d - 1] == '\n')
	{
		input[*ctrl_d - 1] = '\0';
	}

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
	int i, j;
	char *new_str = NULL;

	/* Find the index of the first '#' character */
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
			break;
	}

	/* If no '#' character is found, return the original string */
	if (!input[i])
		return (input);

	/* Find the index of the last non-whitespace character before the '#' character */
	for (j = i - 1; j >= 0; j--)
	{
		if (input[j] == ' ' || input[j] == '\t' || input[j] == ';')
			break;

	}
	if (!new_str)
		return (NULL);

	/* Allocate a new string that contains the characters up to the last non-whitespace character */
	new_str = malloc(sizeof(char) * (j + 2));
	
	/* Copy the characters up to the last non-whitespace character to the new string */
	_memcpy(new_str, input, j + 1);
	new_str[j + 1] = '\0';

	/* Set the remaining part of the original string to null terminator */
	input[j + 1] = '\0';

	/* Copy the contents of the new string to the original string */
	_strcpy(input, new_str);

	/* Free the memory allocated for the new string */
	free(new_str);

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

	for (flag = 1; flag; flag = !ctrl_d)
	{
		if (isatty(STDIN_FILENO))
			prompt();

		input = read_input(&ctrl_d);
		if (ctrl_d != -1)
		{
			input = without_comment(input);
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
		else
		{
			flag = 0;
			free(input);
		}
	}
}
