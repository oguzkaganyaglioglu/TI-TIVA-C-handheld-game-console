//
// Created by Oguz Kagan YAGLIOGLU on Oct 27, 2022.
// www.oguzkagan.xyz
//

#ifndef LIBRARIES_NOKIA5110_INC_NOKIA5110_H_
#define LIBRARIES_NOKIA5110_INC_NOKIA5110_H_

#include "tm4c123gh6pm.h"

#define ROW_LEN         84
#define ROW_COUNT       6

/**
 * SCREEN BUFFER
 */
extern uint8_t screenRows[ROW_COUNT][ROW_LEN];


void displaySendCommand(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, const uint8_t* buffer, uint32_t len);
void displaySendData(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, const uint8_t* buffer, uint32_t len);
void displaySendRow(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, const uint8_t* row, uint8_t rowIDX, uint32_t len);

void displaySetCursorPosition(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, uint8_t cursorPosX, uint8_t cursorPosY);

/*! NOTE:   *_buffer functions won't modify the display.
            It will modify the buffer.
            So If you want to see the change you call displaySendRow after these functions.
*/
void drawInRow_buffer(uint8_t* row, const uint8_t* byteMap, size_t start, size_t len);

/*! NOTE:   *_buffer functions won't modify the display.
            It will modify the buffer.
            So If you want to see the change you call displaySendRow after these functions.
*/
void clearRow_buffer(uint8_t* row, uint32_t start, uint32_t len);



#endif /* LIBRARIES_NOKIA5110_INC_NOKIA5110_H_ */
