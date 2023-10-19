#include "shell.h"

/**
 * my_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @m: the amount of characters to be copied
 * Return: the concatenated string
 */
char *my_strncpy(char *dest, char *src, int m)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < m - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < m)
	{
		j = i;
		while (j < m)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * my_strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *my_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * my_strchr - locates a character in a string
 * @str: the string to be parsed
 * @car: the character to look for
 * Return: (str) a pointer to the memory area str
 */
char *my_strchr(char *str, char car)
{
	do {
		if (*str == car)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
