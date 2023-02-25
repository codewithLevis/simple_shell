#include "shell.h"

/**
* _strlen - finds length of a string
* @s: string
* Return: length of s
*/

int _strlen(const char *s)
{
	int i = 0;

	while (s[++i])
		;

	return (i);
}

/**
* __strdup - Allocate memory and duplicate a string
* @str: string
* Return: a duplicate of string
*/
char *_strdup(const char *str)
{
	int j, i = _strlen(str);
	char *ptr;

	ptr = malloc(sizeof(char) * (i + 1));

	if (ptr == NULL)
		return (NULL);

	j = 0;
	while (str[j])
	{
		ptr[j] = str[j];
		j++;
	}

	ptr[j] = '\0';
	return (ptr);
}

/**
 * _strcmp - compares two strings
 *@s1: string 1
 *@s2: string 2
 *Return: value(comparison differences)
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strchr - finds occurrence of character in a string
 * @s: string to be searched
 * @c: character to search
 * Return: pointer to string where the character was found or NULL
*/

char *_strchr(char *s, char c)
{
	while (*s++)
		if (*s == c)
			return (s);

	return (NULL);
}
