//===========================================================//
// Projet Micro - IMR1 - ENSSAT - 2022							 //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768
// Build Environment   : Keil µVision
// Auteur              : Lou Le Gall
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"
#include "lcd.h"
#include "Timer.h"
#include "memoire_i2c.h"
#include "lpc17xx_i2c.h"

#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include <stdio.h>

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{
	int cptTouch = 0;	   // Compteur de touché de l'écran
	int n = 1;			   // Variable qui permet de ne pas exécuter tous les 10ms (temps d'interruption) dans le while
	uint8_t mesdatas[1];   // Tableau qui stocke les données à transmettre dans la mémoire i2c
	uint8_t mesdataslu[1]; // Tableau vide de données qui récupère les données lues de la mémoire i2c

	// Initialisation des stuctures pour le pin connect block
	PINSEL_CFG_Type funcSDA; // Transfert de données en i2c
	PINSEL_CFG_Type funcSCL; // Clock i2c

	// Initialisation PIN SDA
	funcSDA.Portnum = PINSEL_PORT_0;		   // Numéro du port 0.
	funcSDA.Pinnum = PINSEL_PIN_27;			   // Pin 0.27
	funcSDA.Funcnum = PINSEL_FUNC_1;		   // Car function 01 => 1
	funcSDA.Pinmode = PINSEL_PINMODE_PULLUP;   // Pin en mode pull up : 1
	funcSDA.OpenDrain = PINSEL_PINMODE_NORMAL; // Pas de mode OpenDrain

	// Initialisation PIN SCD
	funcSCL.Portnum = PINSEL_PORT_0;		   // Numéro du port 0.
	funcSCL.Pinnum = PINSEL_PIN_28;			   // Pin 0.28
	funcSCL.Funcnum = PINSEL_FUNC_1;		   // Car function 01 => 1
	funcSCL.Pinmode = PINSEL_PINMODE_PULLUP;   // Pin en mode pull up : 1
	funcSCL.OpenDrain = PINSEL_PINMODE_NORMAL; // Pas de mode OpenDrain

	PINSEL_ConfigPin(&funcSDA); // Initialisation du registre SDA
	PINSEL_ConfigPin(&funcSCL); // Initialisation du registre SCL

	lcd_Initializtion(); // Initialisation de l'ecran LCD
	touch_init();		 // Initialisation du tactile de l'écran LCD

	// Direction du GPIO 0.1 en sortie pour les leds
	GPIO_SetDir(0, 0xF, 1);

	initTimer();				 // Initialisation du Timer
	TIM_Cmd(LPC_TIM0, ENABLE);	 // Lancement du timer
	NVIC_EnableIRQ(TIMER0_IRQn); // Autorisation de l'interruption du Timer

	// I2C
	init_i2c_eeprom(); // Appelle de la fontion i2c

	mesdatas[0] = cptTouch;										// Ajout du compteur de touche d'écran dans le tableau de données
	i2c_eeprom_write_read(30, &mesdatas[0], &mesdataslu[0], 1); // Ecriture et relecture du compteur de touche

	// Boucle infinit
	while (1)
	{
		// Boucle qui permet d'afficher le nombre de touche d'écrans
		if (statu_led == 1)
		{ // si le flag status lcd est à 1 pas d'appuie sur l'écran
			// Si n est à 1 on appelle la fontion d'affichage de l'écran quand il n'y a pas d'appuie
			// On met ensuite n à 0 pour ne pas rappeller la fonction tous les 10ms
			if (n == 1)
			{
				ecran_lcd_not_touch();
				n = 0;
			}
		}
		else
		{ // Si on appuie sur l'écran
			if (n == 0)
			{						  // n est à 0 on rentre dans la boucle et on remet n à 1 pour ne pas rentrer dans la boucle tous les 10ms
				if (!(cptTouch % 10)) // Enregistre tous les 10 fois la variable cpTouch
				{
					mesdatas[0] = cptTouch;										// Ajout de la variable qui compte le nombre de touchés d'écran dans le tableau de données
					i2c_eeprom_write_read(30, &mesdatas[0], &mesdataslu[0], 1); // Ecriture et relecture du compteur de touche dans la mémoire i2c
					sprintf(chaine, "Stocke : %d", mesdataslu[0]);				// Affichage sur l'écran la dernière données lu dans la mémoire i2c
					LCD_write_english_string(10, 40, chaine, White, 0);			// Affiche la dernière donnée stocké dans la mémoire
				}

				ecran_lcd_touch();									// Fonction appeler quand on touche l'écran lcd
				cptTouch++;											// Incrémentaion de la variable cptTouch
				sprintf(chaine, "Nombre de tape : %d", cptTouch);	// Affichage du nombre de touché fait sur l'écran
				LCD_write_english_string(10, 10, chaine, White, 0); // Affichage du nombre de touché fait sur l'écran
			}
			n = 1;
		}
	}
}

//---------------------------------------------------------------------------------------------
#ifdef DEBUG
void check_failed(uint8_t *file, uint32_t line)
{
	while (1)
		;
}
#endif
