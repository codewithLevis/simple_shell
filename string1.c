#include "shell.h"

/**
*_strlen - returns length of a string
*@s: string
*Return: len
*/

int _strlen(const char *s)
{
	int i = 0;

	while (s[++i])
		;
	return (i);
}

/**
*get_int_length - finds length of int data type variable
*@num: integer
*Return: len
*/
int get_int_length(int num)
{
	int length = 0;
	/*special case for 0*/
	if (num == 0)
		return (1);

	if (num < 0)
	{
		length++;/*account for negative sign*/
		num *= -1;/*make num positive for counting digits*/
	}

	while (num > 0)
	{
		length++;
		num /= 10;
	}

	return (length);
}

/**
*_itoa - converts interger to a string
*@n: number to convert
*Return: string of charcters
*/
char *_itoa(int n)
{
	char *buffer;
	unsigned int n_abs = (n < 0) ? -n : n;
	int i, len = get_int_length(n_abs);

	if (n < 0)
		len++;

	buffer = (char *) malloc(len + 1);

	if (buffer == NULL)
	{
		return (NULL);
	}
	buffer[len] = '\0';

	i = len - 1;

	do {
		buffer[i--] = (n_abs % 10) + '0';
		n_abs /= 10;
	} while (n_abs > 0);

	if (n < 0)
	{
		buffer[0] = '-';
	}

	return (buffer);
}

/**
*_memcpy - copies memory area
*@dest: memory area to be filled
*@src: memory area to copy
*@n: number of characters to copy
*Return: string memory location
*/

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i = 0;

	while (i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
*_strdup - returns a pointer to a newly
*allocated space in memory
*@str: sting to duplicate
*Return: string pointer
*/
char *_strdup(char *str)
{
	size_t len = _strlen(str) + 1;
	char *dup = malloc(len * sizeof(char));

	if (str == NULL)
		return (NULL);

	if (dup == NULL)
		return (NULL);

	_memcpy(dup, str, len);

	return (dup);
}
