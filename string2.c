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
	while (*s)
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
	static char *last;
	char *tok_start, *tok_end;

	if (str == NULL)
		str = last;

	str += _strspn(str, delim);

	if (*str == '\0')
		return (NULL);

	tok_start = str;
	tok_end = _strpbrk(tok_start, delim);

	if (tok_end != NULL)
	{
		*tok_end = '\0';
		last = tok_end + 1;
	}
	else
	{
		last = tok_start + _strlen(tok_start);
	}

	return (tok_start);
}

/**
*_strndup - creates a new memory location and
*duplicated a string of specified size
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
*@optr: double pointer to the memory previously allocated.
*@obyte: size, in bytes, of the allocated space of old_ptr.
*@nbyte: new size, in bytes, of the new memory block.
*Return: Returns old_ptr.
*If new_size_bytes == old_size_bytes, returns old_ptr without changes.
*If malloc fails, returns NULL.
*/
char **_realloc_double_ptr(char **optr, unsigned int obytes, unsigned int nbytes)
{
	char **new_ptr;
	unsigned int i;

	if (optr == NULL)
		return (malloc(sizeof(char *) * nbyte));
	if (nbyte == obyte)
		return (optr);
	new_ptr = malloc(sizeof(char *) * nbyte);
	if (new_ptr == NULL)
		return (NULL);
	for (i = 0; i < obyte; i++)
		new_ptr[i] = optr[i];

	free(optr);

	return (new_ptr);
}
