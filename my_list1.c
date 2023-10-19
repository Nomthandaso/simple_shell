#include "shell.h"

/**
 * list_length - determines length of linked list
 * @k: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *k)
{
	size_t j = 0;

	while (k)
	{
		k = k->next;
		j++;
	}
	return (j);
}

/**
 * list_strings - returns an array of strings of the list->str
 * @hd: pointer to first node
 *
 * Return: array of strings
 */
char **list_strings(list_t *hd)
{
	list_t *nd = hd;
	size_t j = list_length(hd), k;
	char **my;
	char *str;

	if (!hd || !j)
		return (NULL);
	my = malloc(sizeof(char *) * (j + 1));
	if (!my)
		return (NULL);
	for (j = 0; nd; nd = nd->next, j++)
	{
		str = malloc(my_strlen(nd->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(my[k]);
			free(my);
			return (NULL);
		}

		str = my_strcpy(str, nd->str);
		my[j] = str;
	}
	my[j] = NULL;
	return (my);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @k: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *k)
{
	size_t j = 0;

	while (k)
	{
		my_puts(conv_number(k->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		my_puts(k->str ? k->str : "(nil)");
		my_puts("\n");
		k = k->next;
		j++;
	}
	return (j);
}

/**
 * nd_starts_with - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @prefix: string to match
 * @d: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nd_starts_with(list_t *nd, char *prefix, char d)
{
	char *q = NULL;

	while (nd)
	{
		q = starts_with(nd->str, prefix);
		if (q && ((d == -1) || (*q == d)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * get_nd_index - gets the index of a node
 * @hd: pointer to list head
 * @nd: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_nd_index(list_t *hd, list_t *nd)
{
	size_t j = 0;

	while (hd)
	{
		if (hd == nd)
			return (j);
		hd = hd->next;
		j++;
	}
	return (-1);
}
