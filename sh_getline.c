#include "hshell.h"
ssize_t readto_bffr(FILE *stream);
size_t write_ln(char *line, size_t cpsize);
static char buffer[BUFFER_SIZE];
static size_t bffri;
static size_t bffrsz;

/**
 * _getline - Custom getline function
 * @line: where the information gathered wil be stored
 * @lnsz: size of the poinnter to write to
 * @stream: Where the data will come from
 * Return: size of the line given by stream
 * -1 if error
 */
ssize_t _getline(char **line, size_t *lnsz, FILE *stream)
{
	size_t tocpy;
	ssize_t totalrd = 0;

	bffri = 0;
	bffrsz = 0;
	if (stream == NULL)
		return (-1);
	if (*line == NULL || *lnsz == 0)
	{
		*lnsz = BUFFER_SIZE;
		*line = malloc(sizeof(char) * (*lnsz));
		if (*line == NULL)
		{
			fprintf(stderr, "Unable to malloc");
			return (-1);
		}
	}

	while (1)
	{
		if (bffri < bffrsz)
		{
			tocpy = write_ln((*line + totalrd), (*lnsz - totalrd));
			totalrd += tocpy;
			if ((*line)[totalrd - 1] == '\n')
			{
				(*line)[totalrd] = '\0';
				return (totalrd);
			}
		}

		if (readto_bffr(stream) <= 0)
		{
			return (totalrd > 0 ? totalrd : -1);
		}

		if (totalrd + bffri > *lnsz)
		{
			*lnsz *= 2;
			*line = realloc(*line, *lnsz);
			if (*line == NULL)
			{
				fprintf(stderr, "Faild to realloc");
				return (-1);
			}
		}
	}
}

/**
 * readto_bffr - reads to buffer from stdin
 * @stream: where to read from
 * Return: size of buffer
 */
ssize_t readto_bffr(FILE *stream)
{
	int fd = fileno(stream);

	if (fd < 0)
		return (-1);
	bffrsz = read(fd, buffer, BUFFER_SIZE);
	if (bffrsz == 0)
		return (0);
	bffri = 0;
	return (bffrsz);
}

/**
 * write_ln - writes from the buffer to line (argv)
 * @line: Where the contents of buffer will go
 * @cpsize: total to copy
 * Return: ammount needed to be copied
 */
size_t write_ln(char *line, size_t cpsize)
{
	size_t tocpy = bffrsz - bffri;

	if (tocpy > cpsize)
		tocpy = cpsize;
	memcpy(line, (buffer + bffri), tocpy);
	bffri += tocpy;
	return (tocpy);
}
