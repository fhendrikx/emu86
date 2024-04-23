//-------------------------------------------------------------------------------
// EMU86 - Solo86 board I/O mapping
//-------------------------------------------------------------------------------

#include "emu-char.h"
#include "emu-mem-io.h"

#include "int-8xxx.h"
#include "timer-8xxx.h"

#include "mem-io-pcxtat.h"

#include <stdio.h>


extern int info_level;


int io_read_byte (word_t p, byte_t * b)
	{
	switch (p)
		{
		case 0x20:
			*b = char_poll();
			break;
		case 0x22:
			char_recv(b);
			break;
		default:
			*b = 0xFF;
			break;
		}

	if (info_level & 4) printf("[ INB %3xh AL %02xh]\n", p, *b);
	return 0;
	}

int io_write_byte (word_t p, byte_t b)
	{
	switch (p)
		{
		case 0x22:
			char_send(b);
			break;
		}
	if (info_level & 4) printf("[OUTB %3xh AL %0xh]\n", p, b);
	return 0;
	}

//-------------------------------------------------------------------------------

int io_read_word (word_t p, word_t * w)
	{
	return 0;
	}

int io_write_word (word_t p, word_t w)
	{
	return 0;
	}

//-------------------------------------------------------------------------------

