typedef int bool;
#define false 0
#define true 1

extern void scrollup(unsigned int);
extern unsigned char print(char *);

extern kY;
extern kattr;
	
void screen(unsigned char n, unsigned char posx, unsigned char posy);
void printresult(int n);
int pow(int a, unsigned char n);

void _start(void)
{
	
	kY=18;
	kattr=0x5E;
	print("un message \n");
	
	kattr=0x4E;
	print("un autre message \n");
	
	scrollup(2);
	
	while(1);
}

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