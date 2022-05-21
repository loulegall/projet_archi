#include "lpc17xx_i2c.h"

void init_i2c_eeprom (){
	I2C_Init(LPC_I2C0,500000); //initialisation de la vitesse du bus 
	I2C_Cmd(LPC_I2C0,ENABLE); //autorise les échanges 
	
}

void i2c_eeprom_write_read(uint16_t addr, uint8_t* data, uint8_t* data_lu, int length){
	
	int i;
	
	I2C_M_SETUP_Type m1; //définition de la structure du master
	
	uint8_t tab_data[100]; //création d'un tableau dans lequel on va stoker les datas et les 8 bit de vrai data
	
	uint8_t supermasque = addr & 0x0FF; // on garde seulement les 8 bites de poid faible de la data
	
	tab_data[0] = supermasque; // on ajoute à l'indice 0 du nouveau tableau le masque de 8 bit de données
	
	// on remplie le nouveau tableau avec le tableau de data passé en paramètre de la fonction
	for (i = 0; i<length; i++){
		tab_data[i+1] = data[i]; //i+1 pour ne pas prendre en compte la case d'indice 1
	}
	
	//----- INITIALISATION DE LA STRUCTURE EN ECRITURE -----//
	m1.sl_addr7bit = 0x50 | (addr >> 8) ; // les premiers bit de l'adresse d'esclava à l'adresse 0 (1010 000)   case memoire ou on ecrit
	m1.tx_data = tab_data; // pointeur vers le tableau de valeur à transmettre 
	m1.tx_length = length + 1; // on transmet 1 octets en plus de la longueur, cette octet comprend le reste de la donnée
	m1.tx_count = 0;
	
	m1.rx_data = NULL;
	m1.rx_length = 0;
	m1.rx_count = 0;
	
	m1.retransmissions_max = 3; //  il retante au max 3 si la donnée echoue
	m1.retransmissions_count = 0; 
	m1.status = 0; 
	
	I2C_MasterTransferData(LPC_I2C0, &m1,I2C_TRANSFER_POLLING); //fait une écriture avec le processeur en mode maitre sur le bus
	
	//----- INITIALISATION DE LA STRUCTURE EN LECTURE -----//
	m1.sl_addr7bit = 0x50 | (addr >> 8) ; // adresse esclave et 3 bit de poid fort de données
	m1.tx_data = tab_data; // pointeur vers le tableau de valeur à transmettre 
	m1.tx_length = 1; // on transmet 1 octets en plus de la longueur, cette octet comprend le reste de la donnée
	m1.tx_count = 0;
	
	m1.rx_data = data_lu;
	m1.rx_length = length;
	m1.rx_count = 0;
	
	m1.retransmissions_max = 3; //  il retante au max 3 si la donnée echoue
	m1.retransmissions_count = 0; 
	m1.status = 0; 
	
	I2C_MasterTransferData(LPC_I2C0, &m1,I2C_TRANSFER_POLLING); //fait une écriture avec le processeur en mode maitre sur le bus
	
}