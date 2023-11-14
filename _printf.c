#include "main.h"

/**
 * _buffer - Prints the contents of the buffer
 * @buff: Array of characters
 * @buff_index: Index at which to add next char
 */
void _buffer(char buff[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buff[0], *buff_index);

	*buff_index = 0;
}

/**
 * _printf - close replica of Printf function
 * @style: style.
 * Return: Printed chars.
 */
int _printf(const char *style, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list list;
	char buff[BUFFER_SIZE];

	if (style == NULL)
		return (-1);

	va_start(list, style);

	i = 0;
	while (style && style[i] != '\0')
	{
		if (style[i] != '%')
		{
			buff[buff_index++] = style[i];
			if (buff_index == BUFFER_SIZE)
				_buffer(buff, &buff_index);
			/* write(1, &style[i], 1);*/
			printed_chars++;
		}
		else
		{
			_buffer(buff, &buff_index);
			flags = _flags(style, &i);
			width = _width(style, &i, list);
			precision = _precision(style, &i, list);
			size = _size(style, &i);
			++i;
			printed = handle_print(style, &i, list, buff,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
		i++;
	}

	_buffer(buff, &buff_index);

	va_end(list);

	return (printed_chars);
}


