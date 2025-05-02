//-------------------------------------------------------------------------------
// EMU86 - Solo86 board I/O mapping
//-------------------------------------------------------------------------------

#include "emu-mem-io.h"
#include "emu-con.h"

#include "int-8xxx.h"
#include "timer-8xxx.h"

#include "mem-io-solo86.h"

#include <stdio.h>


extern int info_level;

//-------------------------------------------------------------------------------

int io_read_byte (word_t p, byte_t * b)
	{
	/*
	if ((p >= 0x20 && p <= 0x21) || (p >= 0xA0 && p <= 0xA1))
		printf("[ INB %3xh AL %02xh]\n", p, *b);
	*/

	word_t k = 0;

	switch (p)
		{
		case INT_CTRL_PORT:         // interrupt control
		case INT_DATA_PORT:
			*b = 0x00;
			break;

		case COM0_CTRL_PORT:		// console
			if (con_poll_key())
			{
				*b = 0x01;
			}
			else
			{
				*b = 0x00;
			}
			break;

		case COM0_DATA_PORT:		// console
			con_get_key(&k);
			if (k == 0x0D)
				k = 0x0A;
			*b = (byte_t) k;
			break;

		default:
			*b = 0xFF;
			break;
		}

	//if (info_level & 4) printf("[ INB %3xh AL %02xh]\n", p, *b);
	return 0;
	}

int io_write_byte (word_t p, byte_t b)
	{
	/*
	if ((p >= 0x20 && p <= 0x21) || (p >= 0xA0 && p <= 0xA1))
		printf("[OUTB %3xh AL %0xh]\n", p, b);
	*/

	switch (p)
		{
		case TIMER_CTRL_PORT:		// timer
		case TIMER_DATA_PORT:
			timer_io_write (p, b);
			break;

		case INT_CTRL_PORT:         // interrupt control
		case INT_DATA_PORT:
			int_io_write (p, b);
			break;

		case COM0_DATA_PORT:		// console
			con_put_char(b, 0);
			break;

		case 0x80:					// I/O delay
			break;

		default:
			if (info_level & 4) printf("[OUTB %3xh AL %0xh]\n", p, b);
		}
	return 0;
	}

//-------------------------------------------------------------------------------

int io_read_word (word_t p, word_t * w)
	{
	int err;

	/*
	if ((p >= 0x20 && p <= 0x21) || (p >= 0xA0 && p <= 0xA1))
		printf("[ INW %3xh AX %04xh]\n", p, *w);
	*/

	if (p & 0x0001) {
		// bad alignment
		err = -1;
		}
	else {
		// no port
		if (info_level & 4) printf("[ INW %3xh AX %04xh]\n", p, *w);
		*w = 0xFFFF;
		err = 0;
		}

	return err;
	}

int io_write_word (word_t p, word_t w)
	{
	int err;

	/*
	if ((p >= 0x20 && p <= 0x21) || (p >= 0xA0 && p <= 0xA1))
		printf("[OUTW %3xh AX %0xh]\n", p, w);
	*/

	if (p & 0x0001) {
		// bad alignment
		err = -1;
		}
	else {
		// no port
		if (info_level & 4) printf("[OUTW %3xh AX %0xh]\n", p, w);
		err = 0;
		}

	return err;
	}

//-------------------------------------------------------------------------------

