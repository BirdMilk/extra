#include "main.h"

/**
 * _size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int _size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = LONG_SIZE;
	else if (format[curr_i] == 'h')
		size = SHORT_SIZE;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}