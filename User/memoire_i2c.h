#include "lpc17xx_i2c.h"

/**
 * Initialisation memoire i2c
 */
void init_i2c_eeprom();

/**
 * Ecriture et Lecture i2c
 * 
 * @param addr : Adresse  des colonnes et des lignes a laquel on écrit la donnees
 * @param data : Donnees a transmettre
 * @param data_lu : Tableau qui permet de retourner les donnees lues
 * @param length : Longueur des donnes a lire et a transmettre
 */
void i2c_eeprom_write_read(uint16_t addr, uint8_t* data, uint8_t* data_lu, int length);
