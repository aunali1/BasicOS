/************************************************************
 * BasicOS Operating System
 * 
 * File: kernel/common.c
 * 
 * Description:
 * 	Functions used to control the manipulation I/O registers
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
 ************************************************************/

#include <bos/k/common.h>

/** Low-level I/O Handling functions **/

// Sends a 8/16/32-bit value on a I/O location
void outb(u16int port, u8int val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

// Receives a 8/16/32-bit value from an I/O location.
u8int inb(u16int port)
{
    u8int ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

// Receives a 8/16/32-bit value from an I/O location.
u16int inw(u16int port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
} 

// Wait for I/O activity
void io_wait(void)
{
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    asm volatile ( "outb %%al, $0x80" : : "a"(0) );
}

/** Memory Handling Functions **/

// Fill the n bytes following p with nulls, return p
void *memclr(void *p, register unsigned long n)
{
	register long *l;
	register char *s;
	register unsigned long m;
	
	l = p;
	m = n / sizeof(long);
	while (m-- > 0) *l++ = 0;
	s = (char *) l;
	n = n % sizeof(long);
	while (n-- > 0) *s++ = 0;
	return(p);
}

// copies n bytes from the object pointed to by s2 into the object pointed to by s1
void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
	char *tmp = s1;
	const char *s = s2;

	while (n--)
		*tmp++ = *s++;

	return s1;
}

// copies n bytes from the object pointed to by s2 into the object pointed to by s1, overwrites overlaping mem locations
void *memmove(void *s1, const void *s2, size_t n)
{
	char *tmp;
	const char *s;

	if (s1 <= s2) {
		tmp = s1;
		s = s2;
		while (n--)
			*tmp++ = *s++;
	} else {
		tmp = s1;
		tmp += n;
		s = s2;
		s += n;
		while (n--)	
			*--tmp = *--s;
	}
	return s1;
}

// copy c into each of the first n bytes of the object pointed to by s
void *memset(void *s, s32int c, size_t n)
{
	char *xs = s;

	while (n--)
		*xs++ = c;
	return s;
}

