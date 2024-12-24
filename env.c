#include "hshell.h"
char *find_var(char *envar, char **env);
char *rm_name(char *var, char *envar);


/**
 * _getenv - test getting the desired env
 * @envar: Environment variable to search for
 * Return: Pointer to desired envrionment variable,
 * NULL if not found
 */
char *_getenv(char *envar)
{
	char *var = NULL;

	if (envar == NULL)
		return (0);
	var = find_var(envar, environ);
	if (var == NULL)
		return (0);
	var = rm_name(var, envar);
	if (var == NULL)
		return (0);

	return (var);
}


/**
 * find_var - finds the desired enfironment variable
 * @envar: Environ var to look for
 * @env: Environment
 * Return: Full environment var, or NULL if fails
 */
char *find_var(char *envar, char **env)
{
	int found;
	size_t i = 0, j, envsize;

	if (envar == NULL || env == NULL)
		return (0);
	envsize = _strlen(envar);
	if (envsize == 0)
		return (0);
	while (env[i] != NULL)
	{
		found = 1;
		for (j = 0; j < envsize; j++)
		{
			if (env[i][j] != envar[j])
				found = 0;
			if (found == 0)
				break;
		}
		if (found)
			return (env[i]);
		i++;
	}
	return (0);
}


/**
 * rm_name - Removes the env variable name from str
 * @var: Variable from environment
 * @envar: name of eniron variable (varname)
 * Return: Pointer variable value
 */
char *rm_name(char *var, char *envar)
{
	size_t evsz;

	if (var == NULL || envar == NULL)
		return (0);

	evsz = _strlen(envar);
	if (evsz == 0)
		return (0);

	var = (var + (evsz + 1));

	return (var);
}
