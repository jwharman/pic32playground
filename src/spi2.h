#ifndef _SPI2_H_
#define _SPI2_H_

#include <stdint.h>

void SPI2_init();


void SPI2_tx8(uint8_t dataTx);

void SPI2_tx16(uint16_t dataTx);

void SPI2_tx32(uint32_t dataTx);



#endif