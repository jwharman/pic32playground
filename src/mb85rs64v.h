#ifndef _MB85RS64V_H_
#define _MB85RS64V_H_

#include <stdint.h>

//FRAM OPCODES

#define FRAM_OP_WREN  0x06 //set write enable latch
#define FRAM_OP_WRDI  0x04 //reset write enable latch
#define FRAM_OP_RDSR  0x05 //read status register
#define FRAM_OP_WRSR  0x01 //write status register
#define FRAM_OP_READ  0x03 //read memory code
#define FRAM_OP_WRITE 0x02 //write memory code
#define FRAM_OP_RDID  0x9F //read device id

//FRAM Size
#define FRAM_ADDRESS_START 0x0000
#define FRAM_ADDRESS_END   0x1FFF


uint8_t byte_read_at_index(uint16_t index);
uint8_t byte_write_at_index(uint16_t index, uint8_t data);


void FRAM_init(void);
void FRAM_service(void);

#endif