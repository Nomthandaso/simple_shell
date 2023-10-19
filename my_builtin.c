#include "shell.h"
/**
 * my_exit - exit the shell
 * @info: Structure containing potential arguments
 * Return: exits with a given exit status (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int checkexit;

	if (info->argv[1])
	{
		checkexit = _erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number:");
			my_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current dir of the process
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int my_cd(info_t *info)
{
	char *m, *directory, buffer[1024];
	int my_chdir;

	m = getcwd(buffer, 1024);
	if (!m)
		my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = my_getenv(info, "HOME=");
		if (!directory)
			my_chdir = chdir((directory = my_getenv(info, "PWD=")) ? directory : "/");
		else
			my_chdir = chdir(directory);
	}
	else if (my_strcmp(info->argv[1], "-") == 0)
	{
		if (!my_getenv(info, "OLDPWD="))
		{
			my_puts(m);
			_putchar('\n');
			return (1);
		}
		my_puts(my_getenv(info, "OLDPWD=")), _putchar('\n');
		my_chdir = chdir((directory = my_getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		my_chdir = chdir(info->argv[1]);
	if (my_chdir == -1)
	{
		print_error(info, "can't cd to ");
		my_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", my_getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current dir of the process
 * @info: Structure containing potentia arguments
 *
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **array;

	array = info->argv;
	my_puts("help call works. Function not yet implemented\n");
	if (0)
		my_puts(*array);
	return (0);
}
