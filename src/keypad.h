#ifndef __KEYPAD_H
#define __KEYPAD_H

#include "stm32f4xx_hal.h"

#define ROW_NUM 4
#define COL_NUM 4

void Keypad_SetRowPins(GPIO_TypeDef* ports[ROW_NUM], uint16_t pins[ROW_NUM]);
void Keypad_SetColPins(GPIO_TypeDef* ports[COL_NUM], uint16_t pins[COL_NUM]);
void Keypad_Init(void);
char Keypad_Scan(void);

#endif
