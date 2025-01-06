#include "hshell.h"


/**
 * sh_fileno - get the file descriptor associated with a stream
 * @stream: pointer to a FILE object
 * Return: file descriptor associated with stream
 */
int sh_fileno(FILE *stream)
{
	if (stream == NULL)
		return (-1);
	return (stream->_fileno);
}
