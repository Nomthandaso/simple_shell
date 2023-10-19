#include "shell.h"
/**
 * my_history - displays the history list
 * @info: structure containingpotential arguments
 * Return: Alaways 0
 */
int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _alias(info_t *info, char *str)
{
	char *i, j;
	int man;

	i = my_strchr(str, '=');
	if (!i)
		return (1);
	j = *i;
	*i = 0;
	man = del_nd_at_index(&(info->alias),
			get_nd_index(info->alias, nd_starts_with(info->alias, str, -1)));
	*i = j;
	return (man);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *i;

	i = my_strchr(str, '=');
	if (!i)
		return (1);
	if (!*++i)
		return (_alias(info, str));
	_alias(info, str);
	return (add_nd_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_a - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on Success, 1 on error
 */
int print_a(list_t *node)
{
	char *s = NULL, *b = NULL;

	if (node)
	{
		s = my_strchr(node->str, '=');
		for (b = node->str; b <= s; b++)
			_putchar(*b);
		_putchar('\'');
		my_puts(s + 1);
		my_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int j = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_a(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		s = my_strchr(info->argv[j], '=');
		if (s)
			set_alias(info, info->argv[j]);
		else
			print_a(nd_starts_with(info->alias, info->argv[j], '='));
	}
	return (0);
}
