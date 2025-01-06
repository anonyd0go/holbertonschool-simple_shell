#include "hshell.h"

/**
* shelline - read a line from the standard input
* @eof_sig: signal for end of file
* Return: a pointer to the line read
*/
char *shelline(int *eof_sig)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t rd;

	fflush(stdout);
	rd = _getline(&line, &len, stdin);
	if (rd == -1)
	{
		free(line);
		printf("\n");
		*eof_sig = 1;
		return (NULL);
	}
	if (rd == 0)
	{
		free(line);
		*eof_sig = 1;
		return (NULL);
	}
	*eof_sig = 0;
	return (line);
}


/**
* getav - Creates the argument vector
* @line: line given to the shell
* Return: pointer to all arguments in the line
*/
char **getav(char *line)
{
	char **args = NULL;
	char *token;
	size_t i = 0;

	if (line == NULL)
		return (0);
	token = _strtok(line, " \n");
	while (token != NULL)
	{
		args = realloc_args(args, i, 1);
		if (args == NULL)
			return (0);
		args[i] = strdup(token);
		if (args[i] == NULL)
		{
			freeargs(args);
			perror("Error: failed strdup");
			return (0);
		}
		token = _strtok(NULL, " \n");
		i++;
	}
	args = realloc_args(args, i, 1);
	if (args == NULL)
		return (0);
	args[i] = NULL;
	return (args);
}

/**
* execute - executes the command
* @args: arguments to execute
* Return: 1 if success, 0 if fails
*/
int execute(char **args)
{
	sll_t *head_path = NULL;
	char *cmd_path;
	int res;

	if (args == NULL || args[0] == NULL)
		return (1);
	head_path = init_path(_getenv("PATH"));
	if (head_path == NULL)
	{
		perror("Error: failed to get PATH");
		return (0);
	}
	cmd_path = cmd_exists(args, head_path);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "Error: command not found\n");
		free_sll(&head_path);
		return (1);
	}
	res = exe_cmd(args, cmd_path);
	free(cmd_path);
	free_sll(&head_path);

	return (res);
}


/**
* exe_cmd - executes the command
* @args: arguments to execute
* @cmd_path: path to command
* Return: 1 if success, 0 if fails
*/
int exe_cmd(char **args, char *cmd_path)
{
	pid_t pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return (0);

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			fprintf(stderr, "Error: %s\n", strerror(errno));
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error: Unable to fork");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}


/**
* flag_prmpt - prints the prompt handling SIGINT
* @sig: signal number
* Return: void
*/
void flag_prmpt(sig_atomic_t sig)
{
	if (sig)
	{
		fflush(stdout);
		sig = 0;
	}
}
