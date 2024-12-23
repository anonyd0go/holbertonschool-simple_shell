#include "args.h"

/**
 * _strtok - Custom strtok fucntion
 * @str: String to tokenize
 * @delim: Delimiter character
 * Return: Pointer to the next_tok tok;
 */
char *_strtok(char *str, const char *delim)
{
    static char *token_line;
    static char *next_tok;
    char *tok;

    if (str)
        token_line = str;
    if (!token_line)
        return (0);
    next_tok = token_line;
    while (*next_tok)
    {
        if (strchr(delim, *next_tok))
        {
            *next_tok = '\0';
            tok = token_line;
            token_line = next_tok + 1;
            return (tok);
        }
        next_tok++;
    }
    tok = token_line;
    token_line = NULL;
    return (tok);
}