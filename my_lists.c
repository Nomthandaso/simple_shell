#include "shell.h"
/**
 * frees_list - frees all nodes of a list
 * @head_pointer: address of pointer to headnode
 *
 * Return: void
 */
void free_list(list_t **head_pointer)
{
	list_t *nd, *next_nd, *hd;

	if (!head_pointer || !*head_pointer)
		return;
	hd = *head_pointer;
	nd = hd;
	while (nd)
	{
		next_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = next_nd;
	}
	*head_pointer = NULL;
}

/**
 * add_nd - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_nd(list_t **hd, const char *str, int num)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	my_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = my_strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * add_nd_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_nd_end(list_t **hd, const char *str, int num)
{
	list_t *new_nd, *nd;

	if (!hd)
		return (NULL);

	nd = *hd;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	my_memset((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = num;
	if (str)
	{
		new_nd->str = my_strdup(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = new_nd;
	}
	else
		*hd = new_nd;
	return (new_nd);
}

/**
 * my_list - prints only the str element of a list_t linked list
 * @k: pointer to first node
 *
 * Return: size of list
 */
size_t my_list(const list_t *k)
{
	size_t j = 0;

	while (k)
	{
		my_puts(k->str ? k->str : "(nil)");
		my_puts("\n");
		k = k->next;
		j++;
	}
	return (j);
}

/**
 * del_nd_at_index - deletes node at given index
 * @hd: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_nd_at_index(list_t **hd, unsigned int index)
{
	list_t *nd, *prev_nd;
	unsigned int j = 0;

	if (!hd || !*hd)
		return (0);

	if (!index)
	{
		nd = *hd;
		*hd = (*hd)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *hd;
	while (nd)
	{
		if (j == index)
		{
			prev_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		j++;
		prev_nd = nd;
		nd = nd->next;
	}
	return (0);
}


