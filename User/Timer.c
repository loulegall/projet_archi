#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_gpio.h"
#include "Timer.h"
#include "global.h" 
void initTimer(){
	// Déclaration structure de lpc17xx_timer.h
	TIM_MATCHCFG_Type configMatch;

	// Configuration de Match Register 0
	configMatch.MatchChannel = 0; //MR0 
	configMatch.IntOnMatch = ENABLE; //Interruption en cas de match
	configMatch.StopOnMatch = DISABLE; // Ne s'arrête pas au match
	configMatch.ResetOnMatch = ENABLE; // Réinitialisation au match
	configMatch.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; // En cas de match pas de changement 
	
	/*
	Interruption toutes les 10ms avec une precision de 500us
	25MHz donc PR = 1250
	Precission = 500us donc 500us*20 = 10ms
	*/
	configMatch.MatchValue = 20; //Nombre d'incrément à atteindre pour 10ms
	//Remplissage config timer avec la précision
	LPC_TIM0 -> PR = 1250; // calcule la fréquenque à chaque fois
	
	TIM_ConfigMatch(LPC_TIM0, &configMatch); // Appel de fonction avec le timer 0 et la configuration de MR0
	
	return;
}

void TIMER0_IRQHandler(void)
{
	uint32_t masque = GPIO_ReadValue(0) & (1<<19); // Lecture du 19e bit sur 32 du GPIO a 1
	
	//----- LED ------//
	count = count +1; // Incrémentation du compteur
	if (count == 50){
		// Modifie la valeur de sortie 1 du GPIO, allume la led
		GPIO_SetValue(0, 1);
	}
	else if (count==100){
		// Remet la GPIO à 0
		GPIO_ClearValue(0, 1);
		// Modifie la valeur de sortie 2 du GPIO		
		GPIO_SetValue(0, 2);
	}
	else if (count == 150){
		// Remet la GPIO à 0
		GPIO_ClearValue(0, 2);
		// Modifie la valeur de sortie 3 du GPIO
		GPIO_SetValue(0, 4);
	}
	else if (count==200){
		// Remet la GPIO à 0
		GPIO_ClearValue(0, 4);
		// Modifie la valeur de sortie 4 du GPIO
		GPIO_SetValue(0, 8);
	}
	else if (count==250){
		// Remet la GPIO à 0
		GPIO_ClearValue(0, 8);
		count=0;	
	}
	
	//----- LCD -----//
	if (masque == (1<<19)){ // Si le 19e bit est à 1 on met le flag de status de l'écran lcd à 1
		statu_led = 1; // Pas appuye
	}
	else{ // Si le 19e bit est à 0 on met le flag de status de l'écran lcd à 0
		statu_led = 0; // Appuye
	}

	// Aquitement de l'interuption, mettre à 0 un bit dans un registre de timer pour dire qu'on a traité l'information
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}
