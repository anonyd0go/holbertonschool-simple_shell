#include "hshell.h"


/**
 * _strlen - gets length of string
 * @str: String to analyze
 * Return: size of str
 */
size_t _strlen(char *str)
{
	size_t size = 0;

	if (str == NULL)
		return (0);
	while (str[size] != '\0')
		size++;

	return (size);
}


/**
 * realloc_args - reallocates memory for argv
 * @args: arguments provided in line
 * @pos: position in the args
 * @size: number to incrase by
 * Return: pointer to new args
 */
char **realloc_args(char **args, size_t pos, size_t size)
{
	if (args == NULL)
	{
		args = malloc(sizeof(char *) * size);
		if (args == NULL)
			return (0);
	}
	else
	{
		args = realloc(args, sizeof(char *) * (pos + size));
		if (args == NULL)
			return (0);
	}
	return (args);
}


/**
 * freeargs - frees the argument vector
 * @args: arguments to free
 * Return: void
 */
void freeargs(char **args)
{
	size_t i = 0;

	if (args == NULL)
		return;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}
