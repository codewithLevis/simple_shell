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
