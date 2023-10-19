#include "shell.h"
/**
 * my_memset - fills memory with a constant byte
 * @ptr: the pointer to the memory area
 * @byte: the byte to fill *ptr with
 * @n: the amount of bytes to be filled
 * Return: (ptr) a pointer to the memory area ptr
 */
char *my_memset(char *ptr, char byte, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		ptr[j] = byte;
	return (ptr);
}

/**
 * free_me - frees a string of strings
 * @pptr: string of strings
 */
void free_me(char **pptr)
{
	char **b = pptr;

	if (!pptr)
		return;
	while (*pptr)
		free(*pptr++);
	free(b);
}

/**
 * my_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_s: byte size of previous block
 * @new_s: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *my_realloc(void *ptr, unsigned int old_s, unsigned int new_s)
{
	char *q;

	if (!ptr)
		return (malloc(new_s));
	if (!new_s)
		return (free(ptr), NULL);
	if (new_s == old_s)
		return (ptr);

	q = malloc(new_s);
	if (!q)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		q[old_s] = ((char *)ptr)[old_s];
	free(ptr);
	return (q);
}
