#include "debug.h"

void screen(unsigned char n, unsigned char posx, unsigned char posy)
{
	unsigned char *video;
	
	video =(unsigned char *)(0xB8000  + 2 * posx + 160 * posy);
	*video = 48 + n;

	*(video + 1) = 0x57;
}

void printresult(int n){
	int i;
	int q;
	unsigned char x=0;
	bool init = false;
	int dec;
	for (i = 2; i>= 0 ; i--){
		dec = pow(10,i);
		q = n / dec;
		if (q!=0) {
			init = true;
		}
		if (init || i==0) {
			screen(q,x,17);
			x++;
		}
		n = n % dec;
	}
}

int pow(int a, unsigned char n){
	if (n==0){
		return 1;
	} else {
		int val = 1;
		int i;
		for (i=1;i<=n;i++){
			val = val * a;
		}
		return val;
	}
}