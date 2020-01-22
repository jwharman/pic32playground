#ifndef _SPI1_H_
#define _SPI1_H_

#include <stdint.h>

void SPI1_init();


void SPI1_tx8(uint8_t dataTx);

void SPI1_tx16(uint16_t dataTx);

void SPI1_tx32(uint32_t dataTx);


uint8_t SPI1_tx8_ret(uint8_t dataTx);

uint16_t SPI1_tx16_ret(uint16_t dataTx);

uint32_t SPI1_tx32_ret(uint32_t dataTx);



uint8_t SPI1_rx8(void);
uint32_t SPI1_rx32(void);

#endif