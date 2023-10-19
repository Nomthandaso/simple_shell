#include "shell.h"

/**
 * my_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @q: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int my_chain(info_t *info, char *buffer, size_t *q)
{
	size_t j = *q;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @b: the char buffer
 * @q: address of current position in buf
 * @i: starting position in buf
 * @l: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *b, size_t *q, size_t i, size_t l)
{
	size_t j = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			b[i] = 0;
			j = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			b[i] = 0;
			j = l;
		}
	}

	*q = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *nd;
	char *q;

	for (i = 0; i < 10; i++)
	{
		nd = nd_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		q = my_strchr(nd->str, '=');
		if (!q)
			return (0);
		q = my_strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *nd;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!my_strcmp(info->argv[j], "$?"))
		{
			replace_str(&(info->argv[j]),
				my_strdup(conv_number(info->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(info->argv[j], "$$"))
		{
			replace_str(&(info->argv[j]),
				my_strdup(conv_number(getpid(), 10, 0)));
			continue;
		}
		nd = nd_starts_with(info->env, &info->argv[j][1], '=');
		if (nd)
		{
			replace_str(&(info->argv[j]),
				my_strdup(my_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_str(&info->argv[j], my_strdup(""));

	}
	return (0);
}

/**
 * replace_str - replaces string
 * @old: address of old string
 * @not_new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **old, char *not_new)
{
	free(*old);
	*old = not_new;
	return (1);
}
