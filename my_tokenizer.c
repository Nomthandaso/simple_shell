#include "shell.h"
/**
 * split_str - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_str(char *str, char *d)
{
	int a, b, c, m, numwords = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!my_delim(str[a], d) && (my_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	r = malloc((1 + numwords) * sizeof(char *));
	if (!r)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (my_delim(str[a], d))
			a++;
		c = 0;
		while (!my_delim(str[a + c], d) && str[a + c])
			c++;
		r[b] = malloc((c + 1) * sizeof(char));
		if (!r[b])
		{
			for (c = 0; c < b; c++)
				free(r[c]);
			free(r);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			r[b][m] = str[a++];
		r[b][m] = 0;
	}
	r[b] = NULL;
	return (r);
}

/**
 * tokenize_str - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **tokenize_str(char *str, char d)
{
	int a, b, c, m, numwords = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	r = malloc((1 + numwords) * sizeof(char *));
	if (!r)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		r[b] = malloc((c + 1) * sizeof(char));
		if (!r[b])
		{
			for (c = 0; c < b; c++)
				free(r[c]);
			free(r);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			r[b][m] = str[a++];
		r[b][m] = 0;
	}
	r[b] = NULL;
	return (r);
}
