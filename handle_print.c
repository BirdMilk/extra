#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @form: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *form, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	form_t form_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', out_int}, {'d', out_int}, {'b', out_bin},
		{'u', out_unsign}, {'o', out_oct}, {'x', out_hexa},
		{'X', out_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', _reverse}, {'R', _rot13}, {'\0', NULL}
	};
	for (i = 0; form_types[i].form != '\0'; i++)
		if (form[*ind] == form_types[i].form)
			return (form_types[i].func(list, buffer, flags, width, precision, size));

	if (form_types[i].form == '\0')
	{
		if (form[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (form[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (form[*ind] != ' ' && form[*ind] != '%')
				--(*ind);
			if (form[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &form[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
