extern void scrollup(unsigned int);
extern unsigned char print(char *);

extern kY;
extern kattr;

#include "debug.h"
#include "types.h"
#include "gdt.h"
#include "screen.h"
	
int main(void);

void _start(void)
{
	
	kY=10;
	kattr=0x5E;
	print("kernel : loading new gdt...\n");
	
	init_gdt();
	
	asm("	movw $0x18, %ax \n \
	movw %ax, %ss \n \
	movl $0x20000, %esp");
	
	main();
}

int main(void)
{
	kattr= 0x4E;
	print("kernel : nouvelle gdt chargee\n");
	
	scrollup(2);

	while(1);
}