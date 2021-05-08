
#include "emu-mem-io.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Memory status

byte_t mem_stat [MEM_MAX];
byte_t code_stat [MEM_MAX];

// TODO: implement data status
// byte_t data_stat [MEM_MAX];

byte_t _break_data_flag = 0;
addr_t _break_data_addr = 0x100000;


// Memory access

void * mem_get_addr (addr_t a)
	{
	if (a >= MEM_MAX)
		{
		printf ("\nfatal: accessing out of memory @ %lXh\n", a);
		// FIXME: hack to stop until error management
		exit (0);
		}

	// Data breakpoint test
	// Will break the main execution loop later

	if (a == _break_data_addr)
		_break_data_flag = 1;

	return (mem_stat + a);
	}


byte_t mem_read_byte (addr_t a)
	{
	byte_t * p = (byte_t *) mem_get_addr (a);
	return *p;
	}

word_t mem_read_word (addr_t a)
	{
	word_t * p = (word_t *) mem_get_addr (a);
	return *p;
	}


int mem_write_byte_0 (addr_t a, byte_t b, byte_t init)
	{
	int err = 0;

	if (a >= ROM_BASE && !init)  // Protect ROM
		{
		printf ("\nwarning: writing byte into ROM @ %lXh\n", a);
		// FIXME: hack to stop until error management
		// exit (0);
		err = -1;
		}
	else
		{
		byte_t * p = (byte_t *) mem_get_addr (a);
		*p = b;
		}

	// No more traced instruction here

	code_stat [a] = 0;

	return err;
	}

int mem_write_word_0 (addr_t a, word_t w, byte_t init)
	{
	int err = 0;

	if (a >= (ROM_BASE - 1) && !init)  // Protect ROM
		{
		printf ("\nwarning: writing word into ROM @ %lxh\n", a);
		// FIXME: hack to stop until error management
		// exit (0);
		err = -1;
		}
	else
		{
		word_t * p = (word_t *) mem_get_addr (a);
		*p = w;
		}

	// No more traced instruction here

	code_stat [a] = 0;
	code_stat [a + 1] = 0;

	return err;
	}

//-------------------------------------------------------------------------------

// Memory reset

void mem_io_reset ()
	{
	// No or uninitialized memory: all bits to 1
	// Used to check if interrupt vector is initialized in op_int()

	memset (mem_stat, 0xFF, sizeof mem_stat);

	// No traced instruction for now

	memset (code_stat, 0x00, sizeof code_stat);
	}

//-------------------------------------------------------------------------------
