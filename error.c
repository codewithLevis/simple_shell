#include "shell.h"

/**
*check_first_character - check if first character are non-white a space (| & ;)
*@input: pointer input string
*@offset: pointer that will be used to return the
*index of the first non-whitespace character in the input string
*Return: -1 (success) or 0 (not true)
*/
int check_first_character(char *input, int *offset)
{
	char *p = input;

	while (*p != '\0')
	{
		if (*p == ' ' || *p == '\t')
		{
			p++;
			continue;
		}

		if (*p == ';' || *p == '|' || *p == '&')
		{
			*offset = p - input;
			return (-1);
		}

		*offset = p - input;
		return (0);
	}
	return (0);
}

/**
*print_shell_error - generate an error message
*that provides context about the syntax error
*@ptr_data: pointer to struct ShellData
*@input: pointer to user's input string
*@idx: represents the index of the character in
*the input string that caused the syntax error
*@t_msg: integer that is either 0 or 1 and is used to determine
*whether a repeated sequence of a symbol is involved in the syntax error
*Return: void
*/

void print_shell_error(ShellData *ptr_data, char *input, int idx, int t_msg)
{
	char *m, *m2, *m3, *err, *counter, **shell;
	int length;

	if (input[idx] == ';')
	{
		if (t_msg == 0)
			m = (input[idx + 1] == ';' ? ";;" : ";");
		else
			m = (input[idx - 1] == ';' ? ";;" : ";");
	}

	if (input[idx] == '|')
		m = (input[idx + 1] == '|' ? "||" : "|");

	if (input[idx] == '&')
		m = (input[idx + 1] == '&' ? "&&" : "&");

	m2 = ": Syntax error: \"";
	m3 = "\" unexpected\n";
	counter = _itoa(ptr_data->command_counter);
	length = _strlen(ptr_data->command_line_args[0]) + _strlen(counter);
	length += _strlen(m) + _strlen(m2) + _strlen(m3) + 2;

	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(counter);
		return;
	}
	
	shell = ptr_data->command_line_args[0];
	sprintf(err, "%s: %s%s%s%s", shell, counter, m2, m, m3);
	err[length] = '\0';
	dprintf(STDERR_FILENO, "%s ", err);
	free(err);
	free(counter);
}

/**
*duplicates - count the number of consecutive occurrences of the same
*character in the character array
*@input: user input
*@i: index
*Return: value of repetition
*/

int duplicates(char *input, int i)
{
	while (*(input - 1) == *input)
	{
		i++;
		input--;
	}
	return (i);
}
	
/**
*check_separator - function checks for syntax 
*errors related to separators
*@input: pointer to user input
*@i: index
*@offset: keep track of the last separator 
*encountered in the input string
*Return: an integer value that represents the index in the
*input string where an error occurs, if any
*/
int check_separator(char *input, int i, char offset)
{
	int count;
	
	while (*input != '\0')
	{
		if (*input == ' ' || *input == '\t')
		{
			input++;
			i++;
			continue;
		}
		if (*input == ';')
		{
			if (offset == '|' || offset == '&' || offset == ';')
				return (i);
		}
		else if (*input == '|')
		{
			if (offset == ';' || offset == '&')
				return (i);
			if (offset == '|')
			{
				count = duplicates(input, 0);
				if (count == 0 || count > 1)
					return (i);
			}
		}
		else if (*input == '&')
		{
			if (offset == ';' || offset == '|')
				return (i);
			if (offset == '&')
			{
				count = duplicates(input, 0);
				if (count == 0 || count > 1)
					return (i);
			}
		}
		offset = *input;
		input++;
		i++;
	}
	return (0);
}

/**
*find_syntax_error - checks for syntax error
*@ptr_data: pointer to struct ShellData
*@input: user's input
*Return: 1 for errors
*/
int find_syntax_error(ShellData *ptr_data, char *input)
{
	int offset = 0;
	int res = check_first_character(input, &offset);

	if (res == -1)
	{
		print_shell_error(ptr_data, input, offset, 0);
		return (1);
	}

	res = check_separator(input + offset, 0, *(input + offset));

	if (res != 0)
	{
		print_shell_error(ptr_data, input, offset, 1);
		return (1);
	}
	return (0);
}
