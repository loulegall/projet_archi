#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_gpio.h"
#include "Timer.h"
#include "global.h" // fichier contenant toutes les d�clarations de variables globales

void initTimer(){
	//d�claration structure de lpc17xx_timer.h
	TIM_MATCHCFG_Type configMatch;

	// Configuration de MR0
	configMatch.MatchChannel = 0; //car MR0 
	configMatch.IntOnMatch = ENABLE; //Interruption au match
	configMatch.StopOnMatch = DISABLE; //S'arrete au match
	configMatch.ResetOnMatch = ENABLE; //R�initialisation au match
	configMatch.ExtMatchOutputType = TIM_EXTMATCH_HIGH; 
	configMatch.MatchValue = 50; //Nombre d'incr�ment � atteindre pour 10ms
	//Remplissage config timer avec la pr�cision
	LPC_TIM0 -> PR = 1250; // calcule la fr�quenque � chaque fois
	
	TIM_ConfigMatch(LPC_TIM0, &configMatch); //Appel de fonction avec le timer 0 et la configuration de MR0
	
	return;
}

void TIMER0_IRQHandler(void)
{
		uint32_t masque = GPIO_ReadValue(0) & (1<<19); //on met dans une variable le bit 19 de la GPIO0
	
	// LED //
	// incr�mentation du compteur
	count = count +1;
	if (count == 50){
		//Modifie la valeur de sortie 1 du GPIO, allume la led
		GPIO_SetValue(0, 1);
	}
	else if (count==100){
		// on remet la GPIO � 0, etteind
		GPIO_ClearValue(0, 1);
		//Modifie la valeur de sortie 2 du GPIO		
		GPIO_SetValue(0, 2);
	}
	else if (count == 150){
		// on remet la GPIO � 0
		GPIO_ClearValue(0, 2);
		//Modifie la valeur de sortie 3 du GPIO
		GPIO_SetValue(0, 4);
	}
	else if (count==200){
		// on remet la GPIO � 0
		GPIO_ClearValue(0, 4);
		//Modifie la valeur de sortie 4 du GPIO
		GPIO_SetValue(0, 8);
	}
	else if (count==250){
		// on remet la GPIO � 0
		GPIO_ClearValue(0, 8);
		count=0;	
	}
	
	// LCD  //
	if (masque == (1<<19)){
		statu_led = 1; //pas appuye
	}
	else{
		statu_led = 0; // appuye
	}

	// aquitement de l'interuption, mettre � 0 un bit dans un registre de timer pour dire qu'on a trait� l'information
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}
