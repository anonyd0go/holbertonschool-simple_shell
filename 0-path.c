#include "hshell.h"

/**
 * list_path - creates a sll of all dirs in PATH
 * @path: Refers to PATH from environ
 * @head: Head of singly linked list
 * Return: Void
 */
sll_t *list_path(sll_t **head, char *path)
{
	sll_t *tmp, *new;
	char *token;

	if (path == NULL)
		return (0);

	token = strtok(path, ":");

	*head = malloc(sizeof(sll_t));
	tmp = *head;
	if (tmp == NULL)
		return (0);
	tmp->path = strdup(token);
	tmp->next = NULL;

	token = strtok(NULL, ":");
	while (token != NULL)
	{
		new = malloc(sizeof(sll_t));
		if (new == NULL)
		{
			free_sll(head);
			return (0);
		}
		new->path = strdup(token);
		new->next = NULL;
		tmp->next = new;
		tmp = tmp->next;

		token = strtok(NULL, ":");
	}

	return (*head);
}


/**
 * free_sll - Frees a singly linked list
 * @head: Head of singly linked list
 * Return: Void
 */
void free_sll(sll_t **head)
{
	sll_t *tmp = *head, *next;

	if (*head == NULL)
		return;

	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->path);
		free(tmp);
		tmp = next;
	}
}

/**
 * sll_size - returns the size of a singly linked list
 * @head: Head of singly linked list
 * Return: Size of singly linked list
 */
size_t sll_size(sll_t *head)
{
	sll_t *tmp = head;
	size_t size = 0;

	if (head == NULL)
		return (0);

	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

/**
 * find_cmd - finds the command in the singly linked list
 * @cmd: Command to find
 * @head: Head of singly linked list
 * Return: Full path to command
 */
char *find_cmd(char *cmd, sll_t *head)
{
	sll_t *tmp = head;
	char *fullpath;
	size_t cmdsize, pathsize;

	if (cmd == NULL || head == NULL)
		return (0);

	if (access(cmd, F_OK) == 0)
		return (strdup(cmd));

	cmdsize = _strlen(cmd);
	while (tmp != NULL)
	{
		pathsize = _strlen(tmp->path);
		fullpath = malloc(sizeof(char) * (pathsize + cmdsize + 2));
		if (fullpath == NULL)
			return (0);
		fullpath = strcpy(fullpath, tmp->path);
		fullpath = strcat(fullpath, "/");
		fullpath = strcat(fullpath, cmd);
		if (access(fullpath, F_OK) == 0)
			return (fullpath);
		free(fullpath);
		tmp = tmp->next;
	}
	return (0);
}

/**
 * init_path - initializes the PATH slingly linked list
 * @path: PATH from environ
 * Return: Head of singly linked list
 */
sll_t *init_path(char *path)
{
	sll_t *head = NULL;
	char *path_cp;

	if (path == NULL)
	{
		perror("Error: failed to get PATH");
		return (0);
	}

	path_cp = strdup(path);
	if (path_cp == NULL)
	{
		perror("Error: failed to copy PATH");
		return (0);
	}
	list_path(&head, path_cp);
	free(path_cp);
	if (head == NULL)
	{
		perror("Error: failed to list path");
		return (0);
	}
	return (head);
}
