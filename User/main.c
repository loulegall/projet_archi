//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2022							 //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768	
// Build Environment   : Keil µVision
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
	  	int cptTouch = 0; // compteur 
	  	int n = 1; // variable qui permet de ne pas exécuter tous les 10ms dans le while
	  	//uint8_t mesdatas[5] ={0,8,9,12,4}; // tableau de données
	  	uint8_t mesdatas[5] ;
	  	uint8_t mesdataslu[5]; // tableau vide de données
					
		// Initialisation PINSEL pour accerder a la mémoire I2C
		PINSEL_CFG_Type funcSDA;
		PINSEL_CFG_Type funcSCL;
	
		// initialisation pin SDA
		funcSDA.Portnum = PINSEL_PORT_0; // numéro du port 0.
		funcSDA.Pinnum = PINSEL_PIN_27; // pin 0.27
		funcSDA.Funcnum = PINSEL_FUNC_1 ; // Car function 01 => 1
		funcSDA.Pinmode = PINSEL_PINMODE_PULLUP; //
		funcSDA.OpenDrain = PINSEL_PINMODE_NORMAL;
	
	
		// initialisation pin SCD
		funcSCL.Portnum = PINSEL_PORT_0; // numéro du port 0.
		funcSCL.Pinnum = PINSEL_PIN_28; // pin 0.28
		funcSCL.Funcnum = PINSEL_FUNC_1 ; // Car function 01 => 1
		funcSCL.Pinmode = PINSEL_PINMODE_PULLUP;
		funcSCL.OpenDrain = PINSEL_PINMODE_NORMAL;
		
		PINSEL_ConfigPin (&funcSDA);
		PINSEL_ConfigPin (&funcSCL);
	
	
		lcd_Initializtion(); // init pinsel ecran et init LCD
		touch_init(); //initialisation du tactile

	 	 // direction du GPIO 0.1 en sortie 
	  	GPIO_SetDir(0, 0xF, 1);
	
		initTimer(); // appelle de la fonction qui appelle la structure du timer
		TIM_Cmd(LPC_TIM0, ENABLE); //lancement du timer
		NVIC_EnableIRQ(TIMER0_IRQn); // autorisation de l'interuption

		
		//I2C
	  	init_i2c_eeprom();
		
		mesdatas[0] = cptTouch; // initialisation de la case d'indice 0
		i2c_eeprom_write_read(30, &mesdatas[0], &mesdataslu[0], 5);
		
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    while(1){
			
			if (statu_led == 1){
				if (n == 1){
					ecran_lcd_not_touch ();
					n = 0;
				}
			}
			else {
				// boucle qui permet d'afficher le nombre de tapes qu'on fait sur l'écran
				if ( n == 0){	
					
						if(!(cptTouch%10)) // on enregistre tous les 10 fois la variable cpTouch
						{
							mesdatas[0] = cptTouch; // ajout variable qui compte le nrb de tape dans tableau de données
							i2c_eeprom_write_read(30, &mesdatas[0], &mesdataslu[0], 5);
							sprintf(chaine, "Stocke : %d",mesdataslu[0]);
							LCD_write_english_string(10,40, chaine, White, 0);
						}
						
						ecran_lcd_touch ();
						cptTouch ++;
						sprintf(chaine, "Nombre de tape : %d",cptTouch);
						LCD_write_english_string(10,10, chaine, White, 0);
				}	
				n = 1;
		}
		}			
}

		

//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
