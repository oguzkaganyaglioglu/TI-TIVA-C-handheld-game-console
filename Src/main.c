//
// Created by Oguz Kagan YAGLIOGLU on 28 October 2022.
// www.oguzkagan.xyz
//

#define CHARACTER_LEN     9
#define ENEMY_LEN         11
#define NUMBER_OF_ENEMIES 6

#define ENEMY_ROW_LEFT_RIGHT_MARGIN 3
#define ENEMY_LEFT_RIGHT_PADDING 1

#define ENEMY_HEALTH      100
#define CHARACTER_DAMAGE  20 

#define CHARACTER_HEALTH  100
#define ENEMY_DAMAGE      10

// the time it takes for the bullet to go from the bottom to the top of the screen
#define BULLET_SPEED_MS  1000 // default speed: 1000 millisecond

// This value indicates how many bullet a player can have on the screen
#define CHARACTER_MAX_BULLET_ON_SCREEN  3
// This value indicates how many bullet each enemy can have on the screen
#define ENEMY_MAX_BULLET_ON_SCREEN      3

#define CHARACTER_BULLET_END_HEIGHT     40 // bottom: 0 & top: 47
#define CHARACTER_BULLET_START_HEIGHT   8  // bottom: 0 & top: 47

#include "tm4c123gh6pm.h"
#include "nokia5110.h"

typedef struct {
  uint8_t x;
  uint8_t y;
  bool done;
} bulletPos_t;

typedef struct {
  uint8_t x; // x position
  uint8_t health;
} enemy_t;

static const uint8_t enemyBytes[ENEMY_LEN] = {
    0x70, 0x5e, 0x12, 0xfb, 0x9e, 0x0e, 0x9e, 0xfb, 0x12, 0x5e, 0x70
};

static const uint8_t characterBytes[CHARACTER_LEN] = {
    // 0x28, 0x14, 0x16, 0x32, 0x18, 0x32, 0x16, 0x14, 0x28 // old character
    0x30, 0x34, 0x3c, 0x1c, 0x18, 0x1c, 0x3c, 0x34, 0x30 // new character
};

GPIO_Handle_t POT;
GPIO_Handle_t BUTTON;

GPIO_Handle_t SPI_MOSI;
GPIO_Handle_t SPI_CLK;

GPIO_Handle_t displayCE;
GPIO_Handle_t displayDC;
GPIO_Handle_t displayRST;

SPI_Handle_t mySPI;

TIMER_Handle_t TIMER1_A_30hz_B_1000hz;

/**
 * POSITION HOLDERS
 *
 * - if the name begins with _xb which means that theposition indicates the start position
 * - if the name begins with _xc which means that theposition indicates the center position
 * - if the name begins with _xe which means that theposition indicates the end position
 *
 * - x indicates whether the position is horizontal or vertical. v = vertical, h = horizontal
 *
 * For example if our character is 3 pixel long, these positions all indicates the same position.
 * Which is the most left side of the screen
 *  _hb = 0
 *  _hc = 1
 *  _hd = 2
 */

size_t characterPos_hb = 0;

bulletPos_t characterBulletPos[CHARACTER_MAX_BULLET_ON_SCREEN];
bulletPos_t enemyBulletPos[NUMBER_OF_ENEMIES][ENEMY_MAX_BULLET_ON_SCREEN];

enemy_t enemies[NUMBER_OF_ENEMIES];

// max value is 4294967295
// That's more than a month, so that should be sufficient
uint32_t millis = 0;

/**
 * @brief Checks whether the time has reached.
 *
 * @param time the future timestamp
 * @param timeoutValue the number of milliseconds to add to the current timestamp
 * @return true  the time has reached and the timer is setted to the future timestamp
 * @return false the time has not reached
 */
bool timeReached(uint32_t* time, uint32_t timeoutValue) {
  if (*time <= millis) {
    *time = millis + timeoutValue;
    return true;
  }
  return false;
}

int main(void)
{

  uint8_t u8_forLoopI;
  uint8_t u8_forLoopJ;
  uint8_t u8_forLoopK;

  /**
   * INITIALIZE POSITION VARIABLES
   **/
  for (u8_forLoopI = 0; u8_forLoopI < CHARACTER_MAX_BULLET_ON_SCREEN; ++u8_forLoopI) {
    characterBulletPos[u8_forLoopI].x = 0;
    characterBulletPos[u8_forLoopI].y = 0;
    characterBulletPos[u8_forLoopI].done = true;
  }

  /**
   * INITIALIZE ENEMIES
   **/
  for (u8_forLoopI = 0; u8_forLoopI < NUMBER_OF_ENEMIES; ++u8_forLoopI) {
    enemies[u8_forLoopI].x = (ENEMY_ROW_LEFT_RIGHT_MARGIN + ENEMY_LEFT_RIGHT_PADDING) + (u8_forLoopI * ((ROW_LEN - (2 * ENEMY_ROW_LEFT_RIGHT_MARGIN)) / NUMBER_OF_ENEMIES));
    enemies[u8_forLoopI].health = ENEMY_HEALTH;
  }


  /**
   * POT PIN CONFIG
   */
  POT.pGPIOx_BaseAddress = GPIO_PORT_AHB_AN9;
  POT.GPIO_PinConfig.PinNumber = GPIO_PIN_AN9;
  POT.GPIO_PinConfig.PinCNF = GPIO_CNF_IN_AN;
  POT.GPIO_PinConfig.PinPuPdControl = GPIO_PU;
  POT.pADCx_BaseAddress = ADC0;
  POT.ADC_PinConfig.ADC_Number = AN9;
  POT.ADC_PinConfig.SR = ADC_SAMPLING_RATE_125K;
  POT.ADC_PinConfig.SS = ADC_SS3;
  POT.ADC_PinConfig.SSCTL = ADC_SSCTL_SIE | ADC_SSCTL_EOS;

  /**
   * BUTTON PIN CONFIG
   */
  BUTTON.pGPIOx_BaseAddress = GPIOF_AHB;
  BUTTON.GPIO_PinConfig.PinNumber = GPIO_PIN_4;
  BUTTON.GPIO_PinConfig.PinCNF = GPIO_CNF_IN;
  BUTTON.GPIO_PinConfig.PinPuPdControl = GPIO_PU;

  /**
   * 5110 DISPLAY PIN CONFIG
   */
  SPI_CLK.pGPIOx_BaseAddress = GPIOD_AHB;
  SPI_CLK.GPIO_PinConfig.PinNumber = GPIO_PIN_0;
  SPI_CLK.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
  SPI_CLK.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
  SPI_CLK.GPIO_PinConfig.PinAltFuncMode = 2;

  SPI_MOSI.pGPIOx_BaseAddress = GPIOD_AHB;
  SPI_MOSI.GPIO_PinConfig.PinNumber = GPIO_PIN_3;
  SPI_MOSI.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
  SPI_MOSI.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
  SPI_MOSI.GPIO_PinConfig.PinAltFuncMode = 2;

  displayCE.pGPIOx_BaseAddress = GPIOE_AHB;
  displayCE.GPIO_PinConfig.PinNumber = GPIO_PIN_2;
  displayCE.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
  displayCE.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
  displayCE.GPIO_PinConfig.PinAltFuncMode = 0;

  displayDC.pGPIOx_BaseAddress = GPIOE_AHB;
  displayDC.GPIO_PinConfig.PinNumber = GPIO_PIN_1;
  displayDC.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
  displayDC.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
  displayDC.GPIO_PinConfig.PinAltFuncMode = 0;

  displayRST.pGPIOx_BaseAddress = GPIOE_AHB;
  displayRST.GPIO_PinConfig.PinNumber = GPIO_PIN_3;
  displayRST.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
  displayRST.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
  displayRST.GPIO_PinConfig.PinAltFuncMode = 0;

  /**
   * 5110 DISPLAY SPI CONFIG
   */
  mySPI.pSPI = SPI1;
  mySPI.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
  mySPI.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
  mySPI.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV_4; // 16/4 = 4Mhz speed
  mySPI.SPI_Config.SPI_DeviceMode = SPI_DeviceMode_MASTER;
  mySPI.SPI_Config.SPI_DFF = SPI_DFF_8BITS;


  GPIO_Init(&POT);
  GPIO_Init(&BUTTON);

  GPIO_Init(&SPI_MOSI);
  GPIO_Init(&SPI_CLK);

  GPIO_Init(&displayCE);
  GPIO_Init(&displayDC);
  GPIO_Init(&displayRST);

  SPI_Init(&mySPI);


  GPIO_WritePin_H(&displayCE, true);
  GPIO_WritePin_H(&displayDC, false);

  // reset the display
  GPIO_WritePin_H(&displayRST, false);
  GPIO_WritePin_H(&displayRST, true);


  const uint8_t cmd_buffer[] = {
  0b00100001, // function set PD = 0 and V = 0, select extended instruction set (H = 1 mode)
  0b10010000, // set VOP; VOP is set to a +16 ´ b [V]
  0b00100000, // function set PD = 0 and V = 0, select normal instruction set (H = 0 mode)
  0b00001100, // display control set normal mode (D = 1 and E = 0)
  0b10000000, // cursor x = 0
  0b01000000  // cursor y = 0
  };

  // confıgure display 
  displaySendCommand(&mySPI, &displayDC, &displayCE, cmd_buffer, 6);

  // clear screen buffer
  for (u8_forLoopI = 0; u8_forLoopI < ROW_COUNT; ++u8_forLoopI) clearRow_buffer(screenRows[u8_forLoopI], 0, ROW_LEN);
  // clear screen
  for (u8_forLoopI = 0; u8_forLoopI < ROW_COUNT; ++u8_forLoopI) displaySendRow(&mySPI, &displayDC, &displayCE, (const uint8_t*)(screenRows[u8_forLoopI]), u8_forLoopI, ROW_LEN);

  /**
    * 30Hz TIMER SETUP
    */

  TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress = TIMER1;
  TIMER1_A_30hz_B_1000hz.TIMER_Config.subtimer = SUBTIMER_AB;
  TIMER1_A_30hz_B_1000hz.TIMER_Config.cfg = TIMER_CFG_16BIT;
  TIMER1_A_30hz_B_1000hz.TIMER_Config.mode = TIMER_MODE_PERIODIC;
  TIMER1_A_30hz_B_1000hz.TIMER_Config.prescaleA = 133 - 1;
  TIMER1_A_30hz_B_1000hz.TIMER_Config.intervalLoadA = 4010 - 1;
  TIMER1_A_30hz_B_1000hz.TIMER_Config.prescaleB = 1 - 1;
  TIMER1_A_30hz_B_1000hz.TIMER_Config.intervalLoadB = 16000 - 1;

  TIMER_Init(&TIMER1_A_30hz_B_1000hz);

  TIMER_IRQSetPriority(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_A, NVIC_IRQ_PRIORITY_1);
  // MAKE SURE THE 1000Hz IRQ HAS THE HIGHEST PRIORITY
  TIMER_IRQSetPriority(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_B, NVIC_IRQ_PRIORITY_0);

  TIMER_IRQConfig_H(&TIMER1_A_30hz_B_1000hz, ENABLE);

  uint32_t adc_value;
  uint32_t timestamp = 0;
  uint32_t timestamp_buttonPress = 0;

  while (true) {
    // READ ADC
    POT.pADCx_BaseAddress->PSSI |= (1 << POT.ADC_PinConfig.SS);
    while ((POT.pADCx_BaseAddress->RIS & (1 << 3)) == 0);
    adc_value = POT.pADCx_BaseAddress->SS[POT.ADC_PinConfig.SS].SSFIFO;
    POT.pADCx_BaseAddress->ISC |= (1 << POT.ADC_PinConfig.SS);

    // CALCULATE POSITION OF THE CHARACTER ON THE SCREEN
    float t = (float)adc_value / 4095.0f;
    TIMER_IRQSuspend(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_A);
    /** DISPLAY SHOULD NOT REFRESH WHILE WE UPDATE THE POSITIONS */
    characterPos_hb = (t * (ROW_LEN - 1));
    if (characterPos_hb < (CHARACTER_LEN / 2)) characterPos_hb = 0;
    else if (characterPos_hb > (ROW_LEN)-(CHARACTER_LEN / 2)) characterPos_hb = (ROW_LEN)-(CHARACTER_LEN);
    else characterPos_hb -= (CHARACTER_LEN / 2);
    if (GPIO_ReadPin_H(&BUTTON) == 0) {
      for (u8_forLoopI = 0; u8_forLoopI < CHARACTER_MAX_BULLET_ON_SCREEN; u8_forLoopI++) {
        if (characterBulletPos[u8_forLoopI].done == false) continue;
        if (!timeReached(&timestamp_buttonPress, BULLET_SPEED_MS / CHARACTER_MAX_BULLET_ON_SCREEN)) break;
        characterBulletPos[u8_forLoopI].x = characterPos_hb + (CHARACTER_LEN / 2);

        characterBulletPos[u8_forLoopI].y = CHARACTER_BULLET_START_HEIGHT;
        characterBulletPos[u8_forLoopI].done = false;
        break;
      }
    }

    if (timeReached(&timestamp, 30)) {
      for (u8_forLoopI = 0; u8_forLoopI < CHARACTER_MAX_BULLET_ON_SCREEN; u8_forLoopI++) {
        if (characterBulletPos[u8_forLoopI].done == true) continue;
        characterBulletPos[u8_forLoopI].y++;
        if (characterBulletPos[u8_forLoopI].y >= CHARACTER_BULLET_END_HEIGHT) {
          characterBulletPos[u8_forLoopI].done = true;
        }
      }
    }

    TIMER_IRQResume(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_A);
  }
  return 0;
}


/**
 * IRQ HANDLERS
 */
void GPIOF_IntHandler() {}
void TIMER1A_Handler() {
  if (TIMER_IRQCausedByThis(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_A)) {

    uint8_t i;

    // clear screen buffer
    for (i = 0; i < ROW_COUNT; ++i) clearRow_buffer(screenRows[i], 0, ROW_LEN);

    for (i = 0; i < CHARACTER_MAX_BULLET_ON_SCREEN; i++) {
      if (characterBulletPos[i].done == true) continue;

      if (characterBulletPos[i].x >= 83) characterBulletPos[i].x = 82; // make sure bullet in the valid area
      if (characterBulletPos[i].x < 1) characterBulletPos[i].x = 1;    // make sure bullet in the valid area

      uint16_t bullet = 0xF000 >> (characterBulletPos[i].y % 8);
      screenRows[(ROW_COUNT - 1) - (characterBulletPos[i].y / 8)][characterBulletPos[i].x - 1] |= (uint8_t)((bullet >> 8) & 0xFF); // draw bullet
      screenRows[(ROW_COUNT - 1) - (characterBulletPos[i].y / 8)][characterBulletPos[i].x] |= (uint8_t)((bullet >> 8) & 0xFF); // draw bullet
      screenRows[(ROW_COUNT - 1) - (characterBulletPos[i].y / 8)][characterBulletPos[i].x + 1] |= (uint8_t)((bullet >> 8) & 0xFF); // draw bullet

      if ((ROW_COUNT - 1) - (characterBulletPos[i].y / 8) >= 1) {
        screenRows[((ROW_COUNT - 1) - (characterBulletPos[i].y / 8) - 1)][(characterBulletPos[i].x) - 1] |= (uint8_t)(bullet & 0xFF); // draw bullet
        screenRows[((ROW_COUNT - 1) - (characterBulletPos[i].y / 8) - 1)][characterBulletPos[i].x] |= (uint8_t)(bullet & 0xFF); // draw bullet
        screenRows[((ROW_COUNT - 1) - (characterBulletPos[i].y / 8) - 1)][characterBulletPos[i].x + 1] |= (uint8_t)(bullet & 0xFF); // draw bullet
      }

    }


    drawInRow_buffer(screenRows[ROW_COUNT - 1], characterBytes, characterPos_hb, CHARACTER_LEN); // draw new data

    // update screen
    for (i = 0; i < ROW_COUNT; ++i) displaySendRow(&mySPI, &displayDC, &displayCE, (const uint8_t*)(screenRows[i]), i, ROW_LEN);

    TIMER_IRQHandling(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_A);
  }
}

void TIMER1B_Handler() {
  if (TIMER_IRQCausedByThis(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_B)) {
    millis++;
    TIMER_IRQHandling(TIMER1_A_30hz_B_1000hz.pTIMERx_BaseAddress, SUBTIMER_B);
  }
}
