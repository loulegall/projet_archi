#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"


#include "global.h" 
#include <stdio.h>
#include <stdint.h>

void ecran_lcd_not_touch (){

		// affichage sur l'écran d'un exemple de 4 carrés de couleur et d'une chaine de caractère
	  sprintf(chaine,"Pas appuye");
	  LCD_write_english_string (70,165,chaine,White,Blue);
	  dessiner_rect(70,60,100,100,1,1,Black,Green);
		dessiner_rect(70,200,100,100,1,1,Black,Red);	 
		
}

void ecran_lcd_touch (){

		// affichage sur l'écran d'un exemple de 4 carrés de couleur et d'une chaine de caractère
	  sprintf(chaine,"Appuye         ");
	  LCD_write_english_string (70,165,chaine,White,Blue);
	  dessiner_rect(70,60,100,100,1,1,Black,Yellow);
		dessiner_rect(70,200,100,100,1,1,Black,Blue);
		
}