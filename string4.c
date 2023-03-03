#include "shell.h"

/**
 * _strrev - reverses a string
 * @str: the string to reverse
 */

void _strrev(char *str)
{
	int len = 0, i, j;
	char temp, *s;

	/* Get length of string */
	while (str[len] != '\0')
		len++;

	s = str;

	/* Swap characters from both ends of the string */
	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		temp = *(s + i);
		*(s + i) = *(s + j);
		*(s + j) = temp;
	}
}

/**
 * _strspn - calculates the length of the initial segment of s which only contains bytes from accept.
 * @s: string to be searched.
 * @accept: string containing the characters to match.
 * Return: the number of bytes in the initial segment of s which consist only of bytes from accept.
 */
unsigned int _strspn(char *s, const char *accept)
{
	unsigned int i, j, match;

	for (i = 0; s[i]; i++)
	{
		match = 0;
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
			{
				match = 1;
				break;
			}
		}
		if (!match)
			break;
	}
	return (i);
}

/**
 * _strpbrk - searches a string for any of a set of bytes.
 * @s: string to be searched.
 * @accept: string containing the characters to match.
 * Return: a pointer to the byte in s that matches one of the bytes in accept, or NULL if no such byte is found.
 */
char *_strpbrk(char *s, char *accept)
{
	unsigned int i, j;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
				return (&s[i]);
		}
	}
	return (NULL);
}

