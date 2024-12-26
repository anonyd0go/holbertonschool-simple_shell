#include "hshell.h"
volatile sig_atomic_t sigint_f = 0;
/**
 * main - entry point of the shell (shelly)
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	char **args;
	int status = 1;

	signal(SIGINT, siginit_hndl);
	do {
		printf("(흫_흫):$ ");
		fflush(stdout);
		flag_prmpt(sigint_f);
		line = shelline();
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