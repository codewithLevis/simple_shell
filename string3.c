#include "shell.h"
/**
*_isdigit- conforms for intergers
*@s: string to be traversed
*Return: 0 or 1
*/
int _isdigit(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
		return (0);
		}
	i++;
	}
	return (1);
}
/**
 * _strcmp - Compare two strings.
 * @s1: A pointer to the first string.
 * @s2: A pointer to the second string.
 * Return: A negative number if s1 is less than s2, 0 if they are equal, or a
 * positive number if s1 is greater than s2.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
*_strcpy - copies ine string to the other
*@src: strinc to be copied
*@dest: copying destination
*Return: dest
*/

char *_strcpy(char *dest, const char *src) 
{
	int i = 0;

	while (src[i] != '\0') 
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
*_realloc - reallocates memory
*@ptr: pointer to current memory block
*@old_size: size of current memory block
*@new_size: size of new memory block
*Return: null or new_memory block
*/

void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (!ptr)
	{
		return (malloc(new_size));
	}

	if (new_size <= old_size)
	{
		return (ptr);
	}

	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}

	return (new_ptr);
}

/**
*_atoi - converts string to an interger
*@str: string to convert
*Return: value converted
*/
int _atoi(const char* str)
{
	int sign = 1;
	int result = 0;
	int i = 0;

	/*Check for a sign character*/
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}

	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
		else
		{
			break;
		}
	}

	return (sign * result);
}
