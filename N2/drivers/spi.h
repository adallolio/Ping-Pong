// Richard McCrae-Lauba, SPI.h - Node 2

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

int SPI_Init(void);
uint8_t SPI_Transcieve(uint8_t data);


#endif /* SPI_H */