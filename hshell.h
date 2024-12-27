#ifndef _SSHELL_H
#define _SSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define EXIT_OK 1
#define EXIT_FAIL 0
#define BI_OK 1
#define BI_FAIL 0
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

/**
 * struct builtins - struct for builtins
 * @name: name of the builtin
 * @f: function pointer to the builtin
 */
typedef struct builtins
{
	char *name;
	int (*f)(char **args);
} builtin_t;

/* Main Utils */
char *shelline(int *eof_sig);
char **getav(char *line);
int execute(char **args);
void flag_prmpt(sig_atomic_t sig);
/*Execute*/
char *cmd_exists(char **args, sll_t *head_path);
int exe_cmd(char **args, char *cmd_path);

/* IO */
ssize_t _getline(char **line, size_t *lnsz, FILE *stream);
char *_strtok(char *str, const char *delim);

/* Environment */
char *_getenv(char *envar);
/*PATH*/
sll_t *list_path(sll_t **head, char *path);
void free_sll(sll_t **head);
size_t sll_size(sll_t *head);
char *find_cmd(char *cmd, sll_t *head);
sll_t *init_path(char *path);

/* Helpers */
size_t _strlen(char *str);
char **realloc_args(char **args, size_t pos, size_t size);
void freeargs(char **args);
void siginit_hndl(int sig);

/* Built-ins */
int exec_builtins(char **args);
int is_exit(char **args);
int is_env(char **args);
int is_getenv(char **args);

#endif
