#include "shell.h"
/**
 * _erratoi - converts a string to an integer
 * @t: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise -1 on error
 */
int _erratoi(char *t)
{
	int i = 0;
	unsigned long int res = 0;

	if (*t == '+')
		t++;
	for (i = 0; t[i] != '\0'; i++)
	{
		if (t[i] >= '0' && t[i] <= '9')
		{
			res *= 10;
			res += (t[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - pritns an error message
 * @info: the parameter & return info struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise -1 on error
 */
void print_error(info_t *info, char *str)
{
	my_eputs(info->fname);
	my_eputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	my_eputs(": ");
	my_eputs(info->argv[0]);
	my_eputs(": ");
	my_eputs(str);
}

/**
 * print_dec - function prints a decimal number (base 10)
 * @input: the input
 * @fd: filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, m = 0;
	unsigned int _abs_, cur;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		m++;
	}
	else
		_abs_ = input;
	cur = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + cur / j);
			m++;
		}
		cur %= j;
	}
	__putchar('0' + cur);
	m++;

	return (m);
}

/**
 * conv_number - converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *conv_number(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char s = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		s = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "012456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (s)
		*--ptr = s;
	return (ptr);
}

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0
 */
void rm_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
