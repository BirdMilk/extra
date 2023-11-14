#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define OPEN(x) (void)(x)
#define BUFFER_SIZE 1024

/* FLAGS */
#define _MINUS 1
#define _PLUS 2
#define _ZERO 4
#define _HASH 8
#define _SPACE 16

/* SIZES */
#define LONG_SIZE 2
#define SHORT_SIZE 1

/**
 * struct form - Struct op
 *
 * @form: The format.
 * @func: The function associated.
 */
struct form
{
	char form;
	int (*func)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct form form_t - Struct op
 *
 * @form: The format.
 * @fm_t: The function associated.
 */
typedef struct form form_t;

int _printf(const char *format, ...);
int handle_print(const char *form, int *i, va_list list, char buffer[], int flags, int width, int precision, int size);

/****************** FUNCTIONS ******************/
/*print chars and strings*/
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*print numbers in different format*/
int out_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int out_bin(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int out_unsign(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int out_oct(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int out_hexa(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int out_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list types, char hex_table[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/*print non printable */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*print memory address*/
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*handle other specifiers*/
int _flags(const char *format, int *i);
int _width(const char *format, int *i, va_list list);
int _precision(const char *format, int *i, va_list list);
int _size(const char *format, int *i);

/*print string in reverse*/
int _reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*print a string in rot 13*/
int _rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* width handler*/
int handle_char(char c, char buffer[], int flags, int width, int precision, int size);
int handle_number(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);
int handle_nums(int ind, char bff[], int flags, int width, int precision, int length, char padd, char extra_c);
int handle_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);


int _isprintable(char);
int insert_hexa(char, char[], int);
int _isdigit(char);

long int change_size(long int num, int size);
long int size_converter(unsigned long int num, int size);

#endif /* MAIN_H */