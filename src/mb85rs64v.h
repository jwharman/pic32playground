#ifndef _MB85RS64V_H_
#define _MB85RS64V_H_

#include <stdint.h>
#include <stdbool.h>

//FRAM OPCODES

#define FRAM_OP_WREN  0x06u //set write enable latch
#define FRAM_OP_WRDI  0x04u //reset write enable latch
#define FRAM_OP_RDSR  0x05u //read status register
#define FRAM_OP_WRSR  0x01u //write status register
#define FRAM_OP_READ  0x03u //read memory code
#define FRAM_OP_WRITE 0x02u //write memory code
#define FRAM_OP_RDID  0x9Fu //read device id

//FRAM Size
#define FRAM_ADDRESS_START 0x0000u
#define FRAM_ADDRESS_END   0x1FFFu


uint8_t byte_read_at_index(uint16_t index);
uint8_t byte_write_at_index(uint16_t index, uint8_t data);

void writeEnable(bool enable);

void write8(uint32_t address, uint8_t value);

void write_test_8(uint16_t address, uint8_t value);
uint8_t read_test_8(uint16_t address);

void FRAM_init(void);
void FRAM_service(void);

uint32_t readDeviceID(void);
uint32_t readStatusRegister(void);

void dumpFRAM(void);
void fillFRAM(void);

#endif