#include "hshell.h"

/**
 * _strtok - Custom strtok fucntion
 * @str: String to tokenize
 * @delim: Delimiter character
 * Return: Pointer to the start_tok tok;
 */
char *_strtok(char *str, const char *delim)
{
	static char *token_ptr;
	char *start_tok = NULL;
	char *end_tok = NULL;

	if (str != NULL)
		token_ptr = str;
	if (token_ptr == NULL)
		return (0);

	start_tok = token_ptr;
	while (*start_tok && strchr(delim, *start_tok))
		start_tok++;
	if (*start_tok == '\0')
	{
		token_ptr = NULL;
		return (0);
	}

	end_tok = start_tok;
	while (*end_tok && !strchr(delim, *end_tok))
		end_tok++;

	if (*end_tok == '\0')
		token_ptr = NULL;
	else
	{
		*end_tok = '\0';
		token_ptr = end_tok + 1;
	}

	return (start_tok);
}
