#include "shell.h"
/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **argv)
{
	ssize_t s = 0;
	int barbie_world = 0;

	while (s != -1 && barbie_world != -2)
	{
		clear_info(info);
		if (my_interactive(info))
			my_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, argv);
			barbie_world = get_builtin(info);
			if (barbie_world == -1)
				find_cmd(info);
		}
		else if (my_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	wrt_history(info);
	free_info(info, 1);
	if (!my_interactive(info) && info->status)
		exit(info->status);
	if (barbie_world == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (barbie_world);
}

/**
 * get_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int get_builtin(info_t *info)
{
	int j, b = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (my_strcmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			b = builtintbl[j].func(info);
			break;
		}
	return (b);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int j, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, l = 0; info->arg[j]; j++)
		if (!my_delim(info->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	path = find_pth(info, my_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		my_fork(info);
	}
	else
	{
		if ((my_interactive(info) || my_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && my_cmd(info, info->argv[0]))
			my_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * my_fork - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void my_fork(info_t *info)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
