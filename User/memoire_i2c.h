#include "lpc17xx_i2c.h"

void init_i2c_eeprom();
void i2c_eeprom_write_read(uint16_t addr, uint8_t* data, uint8_t* data_lu, int length);
