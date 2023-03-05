#include "shell.h"

/**
*my_reallocate - allocate memory for array of strings
*@ptr: pointer to an array of strings
*@old_len: old array size
*@new_len: new array size
*Return: pointer to a newly allocated memory
*/

char **my_reallocate(char **ptr, unsigned int old_len, unsigned int new_len)
{
	char **new_arr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_len));

	if (new_len == old_len)
		return (ptr);

	new_arr = malloc(sizeof(char *) * new_len);

	if (new_arr == NULL)
		return (NULL);

	if (new_len < old_len)
		old_len = new_len;

	for (i = 0; i < old_len; i++)
		new_arr[i] = ptr[i];

	free(ptr);
	return (new_arr);
}

/**
*tokenize - splits input to tokens
*@input: pointer to input
*@delim: delimiter
*Return: an array of strings
*/

char **tokenize(char *input, const char *delim)
{
	size_t bufsize = TOK_BUFSIZE;
	size_t i;
	char *token, **tokens = malloc(bufsize * sizeof(char *));

	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, ": allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = my_strtok(input, delim);

	i = 0;
	while (token != NULL)
	{
		tokens[i++] = _strdup(token);
		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = my_reallocate(tokens, i, bufsize * sizeof(char *));

			if (tokens == NULL)
			{
				dprintf(STDERR_FILENO, ": allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = my_strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}
