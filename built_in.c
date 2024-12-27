#include "hshell.h"

/**
 * execute_builtin - execute builtin commands
 * @args: arguments from command line
 * return: 1 if the command is builtin, 0 otherwise
 */
int exec_builtins(char **args)
{
    size_t i;
    builtin_t builtins[] = {
        {"env", is_env},
        {"getenv", is_getenv},
        {NULL, NULL}
    };

    if (args == NULL || args[0] == NULL)
        return (BI_FAIL);
    for (i = 0; builtins[i].name != NULL; i++)
    {
        if (strcmp(args[0], builtins[i].name) == 0)
        {
            builtins[i].f(args);
            return (BI_OK);
        }
    }
    return (BI_FAIL);
}


/**
 * is_exit - check if the command is exit
 * @args: arguments
 * Return: 1 if the command is exit, 0 otherwise
 */
int is_exit(char **args)
{
    if (args == NULL || args[0] == NULL)
        return (EXIT_FAIL);
    if (strcmp(args[0], "exit") == 0)
        return (EXIT_OK);
    return (EXIT_FAIL);
}


/**
 * is_env - checks to see if the command is env
 * @args: arguments in cli
 * Return: 1 on success, 0 on failure
 */
int is_env(char **args)
{
    size_t i;
    if (args == NULL || args[0] == NULL)
        return (BI_FAIL);
    if (strcmp(args[0], "env") == 0)
    {
        for (i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
        return (BI_OK);
    }
    return (BI_FAIL);
}


/**
 * is_getenv - checks to see if the command is getenv
 * @args: arguments in cli
 * Return: 1 on success, 0 on failure
 */
int is_getenv(char **args)
{
    char *env;
    if (args == NULL || args[0] == NULL)
        return (BI_FAIL);
    if (strcmp(args[0], "getenv") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "getenv: missing argument\n");
            return (BI_OK);
        }
        env = _getenv(args[1]);
        if (env == NULL)
        {
            fprintf(stderr, "getenv: %s: not found\n", args[1]);
            return (BI_OK);
        }
        printf("%s\n", env);
        return (BI_OK);
    }
    return (BI_FAIL);
}