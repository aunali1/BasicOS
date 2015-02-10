/***********************************************************************
 * BasicOS Operating System
 *
 * File: libk/stdio.c
 *
 * Description:
 *      Standard LibC related functions.
 *      This file is part of the BasicOS Kernel LibC.
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#include <libk/string.h>
#include <libk/stdio.h>

#ifdef __GNUC__
#include <stdbool.h>
#include <stdarg.h>
#endif

#ifdef __bos_libk
#include <bos/k/tty.h>
#endif

// Displays a single string onto the VGA BIOS stream.
int _k_puts(const char *s)
{
	return _k_printf("%s\n", s);
}

// write the byte specified by c to the VGA BIOS stream
int _k_putchar(int ic)
{
	char c = (char) ic;
	tty_write(&c, sizeof(c));

	return ic;
}

// shall place output on the VGA BIOS stream
static void _k_print(const char *data, size_t data_length)
{
	for (size_t i = 0; i < data_length; i++)
		_k_putchar((int) ((const unsigned char*) data)[i]); 
}


int _k_printf(const char * __restrict format, ... )
{
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;
 
	while ( *format != '\0' )
	{
		if ( *format != '%' )
		{
		print_c:
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			_k_print(format, amount);
			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format;
 
		if ( *(++format) == '%' )
			goto print_c;
 
		if ( rejected_bad_specifier )
		{
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}
 
		if ( *format == 'c' )
		{
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			_k_print(&c, sizeof(c));
		}
		else if ( *format == 's' )
		{
			format++;
			const char* s = va_arg(parameters, const char*);
			_k_print(s, strlen(s));
		}
		else
		{
			goto incomprehensible_conversion;
		}
	}
 
	va_end(parameters);
 
	return written;
}
