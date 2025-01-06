#include "hshell.h"
void print_prompt(void);
static sig_atomic_t sigint_f = 1;

/**
 * main - entry point of the shell (shelly)
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	char **args;
	int status = 1, eof_sig = 0;
	int interactive = isatty(STDIN_FILENO);

	signal(SIGINT, siginit_hndl);
	do {
		if (interactive)
			print_prompt();
		flag_prmpt(sigint_f);
		line = shelline(&eof_sig);
		if (eof_sig)
			break;
		if (line == NULL)
			continue;
		args = getav(line);
		if (args == NULL)
		{
			free(line);
			perror("Error: failed to get arguments");
			status = 0;
		}
		if (is_exit(args))
		{
			free(line);
			freeargs(args);
			return (0);
		}
		if (exec_builtins(args))
		{
			free(line);
			freeargs(args);
			continue;
		}
		status = execute(args);
		free(line);
		freeargs(args);
	} while (status);
	return (0);
}

/**
 * siginit_hndl - Handles SIGINIT (Ctrl+C)
 * @sig: signal number
 */
void siginit_hndl(int sig)
{
	(void)sig;
	sigint_f = 1;
}

/**
 * print_prompt - prints the prompt
 * Return: void
 */
void print_prompt(void)
{
	printf("(흫_흫):$ ");
	fflush(stdout);
}
