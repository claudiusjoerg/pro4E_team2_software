#include "CRC.h"

uint16_t crc(uint16_t crc, uint8_t Daten){
	uint16_t checksum  = _crc16_update(crc,Daten);
	return checksum;
}