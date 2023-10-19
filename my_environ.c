#include "shell.h"
/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	my_list(info->env);
	return (0);
}

/**
 * my_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @n: env var name
 * Return: the value
 */
char *my_getenv(info_t *info, const char *n)
{
	list_t *node = info->env;
	char *s;

	while (node)
	{
		s = starts_with(node->str, n);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		my_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove an enviroment variable
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int my_unsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		my_eputs("Too few arguments.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);
	return (0);
}

/**
 * pop_env_list - populates env linked list
 * @info: Sturcture containing potential arguments
 * Return: Always 0
 */
int pop_env_list(info_t *info)
{
	list_t *nd = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_nd_end(&nd, environ[j], 0);
	info->env = nd;
	return (0);
}
