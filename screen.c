#include "types.h"

#define RAMSCREEN 0xB8000       /* début de la mémoire vidéo */
#define SIZESCREEN 0xFA0        /* 4000, nombres d'octets d'une page texte */
#define SCREENLIM 0xB8FA0


unsigned int kX = 1;                   /* position courante du curseur à l'écran */
unsigned int kY = 18; 
unsigned char kattr = 0x0E;              /* attributs vidéo des caractères à afficher */


/* 
 * 'scrollup' scrolle l'écran (la console mappée en ram) vers le haut
 * de n lignes (de 0 a 25).
 */
void scrollup(unsigned int n)
{
        unsigned char *video, *tmp;

        for (video = (unsigned char *) RAMSCREEN;
             video < (unsigned char *) SCREENLIM; video += 2) {
                tmp = (unsigned char *) (video + n * 160);

                if (tmp < (unsigned char *) SCREENLIM) {
                        *video = *tmp;
                        *(video + 1) = *(tmp + 1);
                } else {
                        *video = 0;
                        *(video + 1) = 0x07;
                }
        }

        kY -= n;
        if (kY < 1)
                kY = 1;
}

void putcar(volatile char c)
{
        unsigned char *video;
        int i;

        if (c == 10) {          
                kX = 1;
                kY++;
        } else if (c == 9) {    
                kX = kX + 8 - ((kX-1) % 8);
        } else if (c == 13) {   
                kX = 1;
        } else {             
                video = (unsigned char *) (RAMSCREEN + 2 * (kX-1) + 160 * (kY-1));
                *video = c;
                *(video + 1) = kattr;

                kX++;
                if (kX > 80) {
                        kX = 1;
                        kY++;
                }
        }

        if (kY > 25)
                scrollup(kY - 24);
}

/*
 * 'print' affiche à l'écran, à la position courante du curseur, une chaîne
 * de caractères terminée par \0.
 */
void print(char *string)
{

	while (*string != 0){
		putcar(*string);
		string++;
	}

}
