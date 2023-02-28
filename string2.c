#include "shell.h"

/**
*_strncpy - function that copies a string
*@dest: string to copy to
*@src: string to copy from
*@n: bytes to copy
*Return: copied string to a given byte
*/
char *_strncpy(char *dest, char *src, int n)
{
        int i;

        for (i = 0; i < n; i++)
                dest[i] = src[i];

        for (; i < n; i++)
       		dest[i] = '\0';

        return (dest);
}

/**
*_strchr - locates a character in string
*@s: pointer to the string to locate a character
*@c: character to be located
*Return: pointer to the location of the character
*/
char *_strchr(char *s, char c)
{
        while(*s)
        {
                if (*s == c)
                        return (s);
                s++;
        }

        return (NULL);
}

/**
*my_strtok - tokenizes a string
*@str: pointer to a string
*@delim: pointer to array of characters
*Return: token
*/

char *my_strtok(char *str, const char *delim)
{
	static char *next_token = NULL;
	char *token = NULL;
	int i, j, len = _strlen(str);
    
	if (str != NULL)
		next_token = str;

  
	for (i = 0; i < len; i++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (next_token[i] == delim[j])
			{
				token = _strndup(next_token, i);
				if (token == NULL)
				{
					return (NULL);
				}

				next_token += i + 1;

				return (token);
			}
		}
	}

	if (next_token != NULL && *next_token != '\0')
	{
		token = _strdup(next_token);
		next_token = NULL;
	}

	return (token);
}

/**
*_strndup - creates a new memory location and duplicated a string of specified size
*@str: pointer ro string to be duplicated
*@i: bytes
*Return: a pointer to a newly allocated space in memory
*It contains a copy of the string given as a parameter
*/

char *_strndup(char *str, int i)
{
	int j;
	int len = _strlen(str);
	char *copy;

	if (str == NULL)
		return (NULL);

	if (len < i)
		i = len;

	copy = malloc(i + 1);

	if (copy == NULL)
		return (NULL);

	for (j = 0; j < i; j++)
		copy[j] = str[j];
	
	copy[j] = '\0';
	return (copy);
}
/**
*_realloc_double_ptr - reallocates a memory block of a double pointer.
*@old_ptr: double pointer to the memory previously allocated.
*@old_size_bytes: size, in bytes, of the allocated space of old_ptr.
*@new_size_bytes: new size, in bytes, of the new memory block.
*Return: Returns old_ptr.
*If new_size_bytes == old_size_bytes, returns old_ptr without changes.
*If malloc fails, returns NULL.
*/
char **_realloc_double_ptr(char **old_ptr, unsigned int old_bytes, unsigned int new_bytes)
{
	char **new_ptr;
	unsigned int i;

	if (old_ptr == NULL)
		return (malloc(sizeof(char *) * new_bytes));
	if (new_bytes == old_bytes)
		return (old_ptr);
	new_ptr = malloc(sizeof(char *) * new_bytes);
	if (new_ptr == NULL)
		return (NULL);
	for (i = 0; i < old_bytes; i++)
		new_ptr[i] = old_ptr[i];

	free(old_ptr);

	return (new_ptr);
}
