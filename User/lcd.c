#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"

#include "global.h"
#include <stdio.h>
#include <stdint.h>

void ecran_lcd_not_touch()
{

	sprintf(chaine, "Pas appuye");							// Affichage d'une chaine de caractère
	LCD_write_english_string(70, 165, chaine, White, Blue); // Affichage sur l'écran la chaine de caractère
	dessiner_rect(70, 60, 100, 100, 1, 1, Black, Green);	// Dessine un carré vert
	dessiner_rect(70, 200, 100, 100, 1, 1, Black, Red);		// Dessine un carré rouge
}

void ecran_lcd_touch()
{

	sprintf(chaine, "Appuye         ");						// Affichage d'une chaine de caractère
	LCD_write_english_string(70, 165, chaine, White, Blue); // Affichage sur l'écran la chaine de caractère
	dessiner_rect(70, 60, 100, 100, 1, 1, Black, Yellow);	// Dessine un carré Jaune
	dessiner_rect(70, 200, 100, 100, 1, 1, Black, Blue);	// Dessine un carré Bleu
}