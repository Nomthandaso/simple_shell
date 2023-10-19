#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buffer, &len_p, stdin);
#else
		s = my_getline(info, buffer, &len_p);
#endif
		if (s > 0)
		{
			if ((*buffer)[s - 1] == '\n')
			{
				(*buffer)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			rm_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*length = s;
				info->cmd_buf = buffer;
			}
		}
	}
	return (s);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t j, k, length;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	s = input_buffer(info, &buffer, &length);
	if (s == -1)
		return (-1);
	if (length)
	{
		k = j;
		q = buffer + j;

		check_chain(info, buffer, &k, j, length);
		while (k < length)
		{
			if (my_chain(info, buffer, &k))
				break;
			k++;
		}

		j = k + 1;
		if (j >= length)
		{
			j = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = q;
		return (my_strlen(q));
	}

	*buf_p = buffer;
	return (s);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @n: size
 *
 * Return: s
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *n)
{
	ssize_t s = 0;

	if (*n)
		return (0);
	s = read(info->readfd, buffer, READ_BUF_SIZE);
	if (s >= 0)
		*n = s;
	return (s);
}

/**
 * my_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int my_getline(info_t *info, char **ptr, size_t *len)
{
	static char buff[READ_BUF_SIZE];
	static size_t j, l;
	size_t m;
	ssize_t r = 0, s = 0;
	char *q = NULL, *new_p = NULL, *d;

	q = *ptr;
	if (q && len)
		s = *len;
	if (j == l)
		j = l = 0;

	r = read_buffer(info, buff, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	d = my_strchr(buff + j, '\n');
	m = d ? 1 + (unsigned int)(d - buff) : l;
	new_p = my_realloc(q, s, s ? s + m : m + 1);
	if (!new_p)
		return (q ? free(q), -1 : -1);

	if (s)
		my_strncat(new_p, buff + j, m - j);
	else
		my_strncpy(new_p, buff + j, m - j + 1);

	s += m - j;
	j = m;
	q = new_p;

	if (len)
		*len = s;
	*ptr = q;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	my_puts("\n");
	my_puts("$ ");
	_putchar(BUF_FLUSH);
}
