#include "hshell.h"

/**
 * _realloc - reallocate a memory block
 * @ptr: Memory to resize
 * @old_size: Old size of memory
 * @new_size: New size of memory
 * Return: Ptr to modified memory, NULL if it fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	unsigned char *bfr, *new;

    if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (0);
	}
    if (ptr == NULL)
	{
		ptr = malloc(new_size);
		if (ptr == NULL)
			return (0);
		return (ptr);
	}

	bfr = ptr;
	new = malloc(new_size);
	if (new == NULL)
		return (0);
	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new[i] = bfr[i];
	}
	else
	{
		for (i = 0; i < new_size; i++)
			new[i] = bfr[i];
	}

	free(ptr);
	return (new);
}
