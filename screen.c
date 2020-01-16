#include "types.h"

#define RAMSCREEN 0xB8000       /* début de la mémoire vidéo */
#define SIZESCREEN 0xFA0        /* 4000, nombres d'octets d'une page texte */
#define SCREENLIM 0xB8FA0

char kX = 0;                    /* position courante du curseur à l'écran */
char kY = 17;
char kattr = 0x57;              /* attributs vidéo des caractères à afficher */


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
        if (kY < 0)
                kY = 0;
}

void putcar(volatile char c)
{
        volatile char *video;
        int i;

        if (c == 10) {          /* CR-NL */
                kX = 0;
                kY++;
        } else if (c == 9) {    /* TAB */
                kX = kX + 8 - (kX % 8);
        } else if (c == 13) {   /* CR */
                kX = 0;
        } else {                /* autres caractères */
                video = (volatile char *) (RAMSCREEN + 2 * kX + 160 * kY);
                *video = c;
                *(video + 1) = kattr;

                kX++;
                if (kX > 79) {
                        kX = 0;
                        kY++;
                }
        }

        if (kY > 24)
                scrollup(kY - 24);
}

/*
 * 'print' affiche à l'écran, à la position courante du curseur, une chaîne
 * de caractères terminée par \0.
 */
int print()
{
	int k=40;
	volatile char *video;
	char *string="Message a afficher 4";
        kY=17;
        while (*string != 0) {  /* tant que le caractère est différent de 0x0 */
                //putcar(*string);
		video = (volatile char *) (RAMSCREEN + 2 * kX + 160 * kY);
                *video = *string;
                *(video + 1) = 0x57;
		*string++;
		kX++;
        }
	return k;
}
