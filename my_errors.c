#include "shell.h"
/**
 * my_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void my_eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - writes the character d to stderr
 * @d: The character to print
 *
 * Return: On success 1, -1 on error and errno is set appropriately
 */
int _eputchar(char d)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buff[j++] = d;
	return (1);
}

/**
 * my_putfd - writes the character d to given fd
 * @d: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1, -1 on error and errno is set appropriately
 */
int my_putfd(char d, int fd)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buff[j++] = d;
	return (1);
}

/**
 * my_putsfd - pritns an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int my_putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += my_putfd(*str++, fd);
	}
	return (j);
}
