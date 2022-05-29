#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"

char chaine[30]; // buffer pour l'affichage sur le LCD
uint16_t touch_x, touch_y ;

int count = 0; // compteur logiciel
int statu_led; // status du toucher de l'�cran LCD

uint16_t tape;