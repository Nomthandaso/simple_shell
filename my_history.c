#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buffer, *d;

	d = my_getenv(info, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (my_strlen(d) + my_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	my_strcpy(buffer, d);
	my_strcat(buffer, "/");
	my_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * wrt_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wrt_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *nd = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		my_putsfd(nd->str, fd);
		my_putfd('\n', fd);
	}
	my_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rd_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rd_history(info_t *info)
{
	int j, superbass = 0, starships = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + superbass, starships++);
			superbass = j + 1;
		}
	if (superbass != j)
		build_history_list(info, buf + superbass, starships++);
	free(buf);
	info->histcount = starships;
	while (info->histcount-- >= HIST_MAX)
		del_nd_at_index(&(info->history), 0);
	renum_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *nd = NULL;

	if (info->history)
		nd = info->history;
	add_nd_end(&nd, buffer, line_count);

	if (!info->history)
		info->history = nd;
	return (0);
}

/**
 * renum_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_history(info_t *info)
{
	list_t *nd = info->history;
	int j = 0;

	while (nd)
	{
		nd->num = j++;
		nd = nd->next;
	}
	return (info->histcount = j);
}
