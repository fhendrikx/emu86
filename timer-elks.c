//------------------------------------------------------------------------------
// EMU86 - PC/XT/AT timer
//------------------------------------------------------------------------------

#include "emu-int.h"
#include "emu-timer.h"

#include "int-elks.h"

#ifdef __EMSCRIPTEN__
#define TIMER_MAX 1500
#elif SDL
#define TIMER_MAX 3000
#else
#define TIMER_MAX 20000
#endif

static int timer_count = 0;

void timer_proc ()
	{
	timer_count++;
	if (timer_count >= TIMER_MAX)
		{
		int_line_set (INT_LINE_TIMER, 1);
		timer_count = 0;
		}
	else
		{
		int_line_set (INT_LINE_TIMER, 0);
		}
	}

void timer_init ()
	{
	}
