#include "main.h"
#include <stdint.h>

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFFER_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	OPEN(width);
	OPEN(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	OPEN(precision);

	num_addrs = (unsigned long)(uintptr_t)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & _ZERO) && !(flags & _MINUS))
		padd = '0';
	if (flags & _PLUS)
		extra_c = '+', length++;
	else if (flags & _SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFFER_SIZE - i - 1));*/
	return (handle_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes s1 hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	OPEN(flags);
	OPEN(width);
	OPEN(precision);
	OPEN(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (_isprintable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += insert_hexa(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * _reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int _reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, cnt = 0;

	OPEN(buffer);
	OPEN(flags);
	OPEN(width);
	OPEN(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		OPEN(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		cnt++;
	}
	return (cnt);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * _rot13 - Print a string s1 rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int _rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char rts;
	char *str;
	unsigned int i, j;
	int cnt = 0;
	char s1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char s2[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	OPEN(buffer);
	OPEN(flags);
	OPEN(width);
	OPEN(precision);
	OPEN(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; s1[j]; j++)
		{
			if (s1[j] == str[i])
			{
				rts = s2[j];
				write(1, &rts, 1);
				cnt++;
				break;
			}
		}
		if (!s1[j])
		{
			rts = str[i];
			write(1, &rts, 1);
			cnt++;
		}
	}
	return (cnt);
}