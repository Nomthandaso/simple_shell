#include "shell.h"
/**
 * my_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int my_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @str_path: the PATH string
 * @strt: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *str_path, int strt, int stop)
{
	static char buffer[1024];
	int j = 0, l = 0;

	for (l = 0, j = strt; j < stop; j++)
		if (str_path[j] != ':')
			buffer[l++] = str_path[j];
	buffer[l] = 0;
	return (buffer);
}

/**
 * find_pth - finds this cmd in the PATH string
 * @info: the info struct
 * @pth_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_pth(info_t *info, char *pth_str, char *cmd)
{
	int j = 0, curr_pth = 0;
	char *path;

	if (!pth_str)
		return (NULL);
	if ((my_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (my_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pth_str[j] || pth_str[j] == ':')
		{
			path = duplicate_chars(pth_str, curr_pth, j);
			if (!*path)
				my_strcat(path, cmd);
			else
			{
				my_strcat(path, "/");
				my_strcat(path, cmd);
			}
			if (my_cmd(info, path))
				return (path);
			if (!pth_str[j])
				break;
			curr_pth = j;
		}
		j++;
	}
	return (NULL);
}
