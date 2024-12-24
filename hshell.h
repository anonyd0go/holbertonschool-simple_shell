#ifndef _SSHELL_H
#define _SSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024
extern char **environ;

/**
 * struct singly - Singly linked list for PATH
 * @path: one of the paths in PATH
 * @next: ptr to next node
 */
typedef struct singly
{
	char *path;
	struct singly *next;
} sll_t;

/* Main Utils */
char *shelline(void);
char **getav(char *line);
int execute(char **args);

/* IO */
ssize_t _getline(char **line, size_t *lnsz, FILE *stream);
char *_strtok(char *str, const char *delim);

/* Environment */
char *_getenv(char *envar);
/*PATH*/
sll_t *list_path(sll_t **head, char *path);
void free_sll(sll_t **head);
size_t sll_size(sll_t *head);

/* Helpers */
size_t _strlen(char *str);
char **realloc_args(char **args, size_t pos, size_t size);
void freeargs(char **args);

#endif
