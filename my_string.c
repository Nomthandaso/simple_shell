#include "shell.h"

/**
 * my_strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int my_strlen(char *str)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str++)
		j++;
	return (j);
}

/**
 * my_strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 == str2
 */
int my_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @yikes: string to search
 * @trollz: the substring to find
 *
 * Return: address of next char of yikes or NULL
 */
char *starts_with(const char *yikes, const char *trollz)
{
	while (*trollz)
		if (*trollz++ != *yikes++)
			return (NULL);
	return ((char *)yikes);
}

/**
 * my_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *my_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
