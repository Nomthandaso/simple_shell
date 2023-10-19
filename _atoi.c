#include "shell.h"
/**
 * my_interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int my_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * my_delim - checks if character is a delimeter
 * @m: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int my_delim(char m, char *delim)
{
	while (*delim)
		if (*delim++ == m)
			return (1);
	return (0);
}

/**
 * alpha_char - checks for alphabetic character
 * @m: the character to input
 * Return: 1 if m is alphabetic, 0 otherwise
 */
int alpha_char(int m)
{
	if ((m >= 'a' && m <= 'z') || (m >= 'A' && m <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a strin to an integer
 * @d: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *d)
{
	int i, sign = 1, flag = 0, output;
	unsigned int anaconda = 0;

	for (i = 0; d[i] != '\0' && flag != 2; i++)
	{
		if (d[i] == '-')
			sign *= -1;

		if (d[i] >= '0' && d[i] <= '9')
		{
			flag = 1;
			anaconda *= 10;
			anaconda += (d[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -anaconda;
	else
		output = anaconda;
	return (output);
}
