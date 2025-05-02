//------------------------------------------------------------------------------
// EMU86 - 8259 interrupt controller (PC/XT/AT)
//------------------------------------------------------------------------------

#include "emu-int.h"

#include "int-8xxx.h"

#include "mem-io-solo86.h"


int _int_line_max = INT_LINE_MAX;
int _int_prio_max = INT_PRIO_MAX;

// All edge triggered for PC/XT/AT

int _int_mode [INT_LINE_MAX] =
	{ 1, 1, 1, 1, 1, 1, 1, 1};

int _int_prio [INT_LINE_MAX] =
	{ 0, 1, 2, 3, 4, 5, 6, 7};

int _int_vect [INT_LINE_MAX] =
	{ 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27 };

int _int_mask [INT_LINE_MAX] =
	{ 0, 1, 1, 1, 1, 1, 1, 1};  // timer unmasked by default

// Initialized to zero by CRT
int _int_req  [INT_LINE_MAX];
int _int_serv [INT_LINE_MAX];

// PIC I/O write

int int_io_write (word_t p, byte_t b)
	{
	switch(p)
		{
		case INT_CTRL_PORT:
			break;
		case INT_DATA_PORT:
			int_end_prio ();
			break;
		}
	return 0;
	}


// PIC initialization

void int_init (void)
	{
	}
