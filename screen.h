#include "types.h"

#ifdef __SCREEN__

#define RAMSCREEN 0xB8000       /* début de la mémoire vidéo */
#define SIZESCREEN 0xFA0        /* 4000, nombres d'octets d'une page texte */
#define SCREENLIM 0xB8FA0


unsigned int kX = 1;                   /* position courante du curseur à l'écran */
unsigned int kY = 9; 
unsigned char kattr = 0x07;              /* attributs vidéo des caractères à afficher */

#else

extern unsigned int kX;
extern unsigned int kY;
extern unsigned char kattr;

#endif

void scrollup(unsigned int);
void putcar(volatile char);
void print(char*);