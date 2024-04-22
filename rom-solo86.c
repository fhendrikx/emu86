//------------------------------------------------------------------------------
// EMU86 - Solo86 custom ROM
//------------------------------------------------------------------------------

#include "emu-int.h"
#include "emu-mem-io.h"

#include <stdlib.h>


// ROM stub initialization

void rom_init (void)
	{
	}

int rom_image_load (char * path)
	{
	return 1;  // error
	}

void rom_term (void)
	{
	}


// Interrupt handler table

int_num_hand_t _int_tab [] = {
	{ 0,    NULL    }
	};
