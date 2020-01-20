#include "debug.h"
#include "types.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"

void init_pic(void);
	
int main(void);

void _start(void)
{
	
	kY=10;
	kattr=0x5E;
	
	print("kernel : initialisation du noyau\n");
	
	init_idt();
	print("kernel : idt chargee\n");
	
	init_pic();
	print("kernel : pic configure\n");
	
	
	init_gdt();
	
	asm("	movw $0x18, %ax \n \
	movw %ax, %ss \n \
	movl $0x20000, %esp");
	
	main();
}

int main(void)
{

	print("kernel : nouvelle gdt chargee\n");
	
	sti;
	
	kattr= 0x4E;
	print("kernel : interruption permise\n");
	
	kattr = 0x07;
	
	scrollup(5);
	
	print(">>");
	
	show_cursor();
	
	while(1);
}