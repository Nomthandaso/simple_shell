#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @vari: the string env var property
 */
int _unsetenv(info_t *info, char *vari)
{
	list_t *node = info->env;
	size_t j = 0;
	char *q;

	if (!node || !vari)
		return (0);

	while (node)
	{
		q = starts_with(node->str, vari);
		if (q && *q == '=')
		{
			info->env_changed = del_nd_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @vari: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *vari, char *val)
{
	char *buffer = NULL;
	list_t *node;
	char *q;

	if (!vari || !val)
		return (0);

	buffer = malloc(my_strlen(vari) + my_strlen(val) + 2);
	if (!buffer)
		return (1);
	my_strcpy(buffer, vari);
	my_strcat(buffer, "=");
	my_strcat(buffer, val);
	node = info->env;
	while (node)
	{
		q = starts_with(node->str, vari);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_nd_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
