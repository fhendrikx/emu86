
#pragma once

#include "emu-types.h"

// Video
// TODO: move to con-video.h

#define VID_COLS		80
#define VID_LINES		25
#define VID_SIZE		0x4000		// 16k
#define VID_PAGE_SIZE	(VID_COLS * 2 * VID_LINES)

// 8253/8254 Timer
#define TIMER_DATA_PORT	0x00
#define TIMER_CTRL_PORT	0x06

// interrupt control
#define INT_CTRL_PORT	0x18
#define INT_DATA_PORT	0x1A

// console
#define COM0_CTRL_PORT  0x20
#define COM0_DATA_PORT  0x22

extern byte_t crtc_curhi, crtc_curlo;
extern int vid_minx, vid_miny;
extern int vid_maxx, vid_maxy;

int vid_base(void);
void update_dirty_region (int x, int y);
void reset_dirty_region ();
