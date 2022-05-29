#include "lpc17xx_i2c.h"

void init_i2c_eeprom()
{
	I2C_Init(LPC_I2C0, 500000); // Initialisation de la vitesse du bus à 500KHz
	I2C_Cmd(LPC_I2C0, ENABLE);	// Autorise les échanges en i2c
}

void i2c_eeprom_write_read(uint16_t addr, uint8_t *data, uint8_t *data_lu, int length)
{

	int i; // Compteur qui permet d'incrementer de la boucle for

	I2C_M_SETUP_Type m1; // Definition de la structure du master

	uint8_t tab_data[100]; // Creation d'un tableau dans lequel on va stoker les datas plus les 8 bits d'adresse de ligne de la mémoire i2c

	uint8_t supermasque = addr & 0x0FF; // Garde seulement les 8 bits de poids faible de l'adresse de la data

	tab_data[0] = supermasque; // Ajoute a l'indice 0 du nouveau tableau le masque de 8 bit de données

	// Remplie le nouveau tableau avec le tableau de data passe en parametre de la fonction
	for (i = 0; i < length; i++)
	{
		tab_data[i + 1] = data[i]; // i+1 pour ne pas prendre en compte la case d'indice 0
	}

	//----- INITIALISATION DE LA STRUCTURE EN ECRITURE -----//
	m1.sl_addr7bit = 0x50 | (addr >> 8); // Adresse esclave, case memoire ou on ecrit (adresse de la mémoire : 1010 + 3 bit de poid fort)
	m1.tx_data = tab_data;				 // Pointeur vers le tableau de valeur a transmettre
	m1.tx_length = length + 1;			 // On transmet 1 octet en plus de la longueur, cette octet comprend le reste de la donnee
	m1.tx_count = 0;					 // Compteur de données a 0 car on à pas commence à envoyer

	// Pas de lecture
	m1.rx_data = NULL;
	m1.rx_length = 0;
	m1.rx_count = 0;

	m1.retransmissions_max = 3;	  //  Nombre de retransmission total en cas d'echec
	m1.retransmissions_count = 0; // On commence a 0
	m1.status = 0;

	I2C_MasterTransferData(LPC_I2C0, &m1, I2C_TRANSFER_POLLING); // Fait une ecriture avec le processeur en mode maitre sur le bus

	//----- INITIALISATION DE LA STRUCTURE EN LECTURE -----//
	m1.tx_data = tab_data; // Adresse de la ligne à lire
	m1.tx_length = 1;	   // Taille d'1 octet
	m1.tx_count = 0;	   // Compteur de données a 0 car on à pas commence à envoyer

	m1.rx_data = data_lu;  // Tableau ou on stocke les donees lues
	m1.rx_length = length; // Longueur des donnees a lire
	m1.rx_count = 0;	   // Compteur de données a 0 car on à pas commence à lire

	m1.retransmissions_max = 3; //  Nombre de retransmission total en cas d'echec
	m1.retransmissions_count = 0;
	m1.status = 0;

	I2C_MasterTransferData(LPC_I2C0, &m1, I2C_TRANSFER_POLLING); // Fait une ecriture avec le processeur en mode maitre sur le bus
}