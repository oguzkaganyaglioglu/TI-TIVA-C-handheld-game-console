//
// Created by Oguz Kagan YAGLIOGLU on Oct 27, 2022.
// www.oguzkagan.xyz
//

#include "nokia5110.h"

/**
 * SCREEN BUFFER
 */
uint8_t screenRows[ROW_COUNT][ROW_LEN];

/*
 * NUMBERS FONT
 */
static const uint8_t numbers[10][4] = {
// '0', 4x5px
{0x0e, 0x11, 0x11, 0x0e},
// '1', 3x5px
{ 0x12, 0x1f, 0x10, 0x0},
// '2', 4x5px
{0x12, 0x19, 0x15, 0x12},
// '3', 4x5px
{0x0a, 0x11, 0x15, 0x0a},
// '4', 4x5px
{0x0c, 0x0a, 0x1f, 0x08},
// '5', 4x5px
{0x17, 0x15, 0x15, 0x09},
// '6', 4x5px
{0x0e, 0x15, 0x15, 0x08},
// '7', 4x5px
{0x01, 0x01, 0x19, 0x06},
// '8', 4x5px
{0x0a, 0x15, 0x15, 0x0a},
// '9', 4x5px
{0x02, 0x05, 0x15, 0x0e}
};

void displaySendCommand(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, const uint8_t* buffer, uint32_t len) {
    // Select command mode
    GPIO_WritePin_H(dc, false);
    // enable chip
    GPIO_WritePin_H(ce, false);

    // send command
    SPI_SendData_blocking(spi->pSPI, buffer, len);

    //disable chip
    GPIO_WritePin_H(ce, true);
    // Select data mode
    GPIO_WritePin_H(dc, true);
}

void displaySendData(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, const uint8_t* buffer, uint32_t len) {
    // Select data mode
    GPIO_WritePin_H(dc, true);
    // enable chip
    GPIO_WritePin_H(ce, false);

    // send command
    SPI_SendData_blocking(spi->pSPI, buffer, len);
    //disable chip
    GPIO_WritePin_H(dc, true);
}

void displaySendRow(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, const uint8_t* row, uint8_t rowIDX, uint32_t len) {
    // check if the given row valid
    if (rowIDX >= ROW_COUNT || len > ROW_LEN) return;

    displaySetCursorPosition(spi, dc, ce, 0, rowIDX);
    displaySendData(spi, dc, ce, (row), len);
}

void displaySetCursorPosition(SPI_Handle_t* spi, GPIO_Handle_t* dc, GPIO_Handle_t* ce, uint8_t cursorPosX, uint8_t cursorPosY) {
    // check if the given position is valid
    if (cursorPosX >= ROW_COUNT || cursorPosY >= ROW_LEN) return;

    uint8_t buffer[3] = {
        0b00100000, // function set PD = 0 and V = 0, select normal instruction set (H = 0 mode)
        0b10000000, // cursor x = 0
        0b01000000 // cursor y = 0
    };
    buffer[1] |= cursorPosX; // set cursor pos x
    buffer[2] |= cursorPosY; // set cursor pos y

    // set cursor position
    displaySendCommand(spi, dc, ce, buffer, 3);
}

void clearRow_buffer(uint8_t* row, size_t start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) row[start + i] = 0;
}

void drawInRow_buffer(uint8_t* row, const uint8_t* byteMap, size_t start, size_t len) {
    size_t i;
    for (i = 0; i < len && (start + i) < ROW_LEN; i++) row[start + i] |= byteMap[i];
}


uint8_t printNumber_buffer(uint32_t number, uint8_t screenPosX, uint8_t screenPosY) {
    if (number >= 10) screenPosX = printNumber_buffer(number / 10, screenPosX, screenPosY);
    number %= 10;
    uint8_t i = 0, s = 4;
    if (number == 1) s = 3;
    uint16_t tmpFont;
    for (i = 0; i < s; ++i) {
        if (screenPosX >= ROW_LEN) break; // stop drawing if it overflows the screen
        tmpFont = ((uint16_t)numbers[number][i]) << (screenPosY % 8);

        screenRows[screenPosY / 8][screenPosX] |= (uint8_t)((tmpFont) & 0xFF);
        if ((screenPosY / 8) >= 1)
            screenRows[(screenPosY / 8) + 1][screenPosX] |= (uint8_t)((tmpFont >> 8) & 0xFF);
        screenPosX++;
    }
    screenPosX += 1; // space for the next character
    return screenPosX;
}
