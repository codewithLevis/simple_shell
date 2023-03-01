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
	char *new_str;
	int i = 0, j = 0;
	int len = _strlen(input);

	new_str = malloc(sizeof(char) * (len + 1));

	while (input[i] != '\0')
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(new_str);
				free(input);
				return (NULL);
			}
			break;
		}

		new_str[j] = input[i];
		i++;
		j++;
		}

		new_str[j] = '\0';
		input = _realloc(input, i, sizeof(char) * (j + 1));

		if (input != NULL)
		{
			_strcpy(input, new_str);
		}

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
			void prompt(void);

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
			flag = split_commands(ptr, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			flag = 0;
			free(input);
		}
	}
}
