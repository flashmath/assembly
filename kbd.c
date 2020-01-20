#include "types.h"
#include "screen.h"
#include "io.h"

void move_cursor(u8 x, u8 y)
{
	u16 c_pos;
	
	c_pos = y * 80 + x;
	outb(0x3d4, 0x0f);
	outb(0x3d5, (u8) c_pos);
	outb(0x3d4, 0x0e);
	outb(0x3d5, (u8) (c_pos >> 8));
}

void show_cursor(void){
	move_cursor(kX-1,kY-1);
}

void initcommand(void){
    kX=1;
	++kY;
	print(">>");
	show_cursor();
	if (kY>25) {
		scrollup(1);
	}
}