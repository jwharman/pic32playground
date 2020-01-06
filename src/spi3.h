#ifndef _SPI3_H_
#define _SPI3_H_

#include <stdint.h>

void SPI3_init();


void SPI3_tx8(uint8_t dataTx);

void SPI3_tx16(uint16_t dataTx);

void SPI3_tx32(uint32_t dataTx);



#endif