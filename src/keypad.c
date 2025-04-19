#include "keypad.h"

static GPIO_TypeDef* rowPorts[ROW_NUM];
static uint16_t rowPins[ROW_NUM];

static GPIO_TypeDef* colPorts[COL_NUM];
static uint16_t colPins[COL_NUM];

const char keymap[ROW_NUM][COL_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void Keypad_SetRowPins(GPIO_TypeDef* ports[ROW_NUM], uint16_t pins[ROW_NUM]) {
    for (int i = 0; i < ROW_NUM; i++) {
        rowPorts[i] = ports[i];
        rowPins[i] = pins[i];
    }
}

void Keypad_SetColPins(GPIO_TypeDef* ports[COL_NUM], uint16_t pins[COL_NUM]) {
    for (int i = 0; i < COL_NUM; i++) {
        colPorts[i] = ports[i];
        colPins[i] = pins[i];
    }
}

void Keypad_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    for (int i = 0; i < COL_NUM; i++) {
        GPIO_InitStruct.Pin = colPins[i];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(colPorts[i], &GPIO_InitStruct);
    }

    for (int i = 0; i < ROW_NUM; i++) {
        GPIO_InitStruct.Pin = rowPins[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(rowPorts[i], &GPIO_InitStruct);
        HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_SET);
    }
}

char Keypad_Scan(void) {
    for (int row = 0; row < ROW_NUM; row++) {
        HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_RESET);

        for (int col = 0; col < COL_NUM; col++) {
            if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                HAL_Delay(20);
                if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                    while (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_SET);
                    return keymap[row][col];
                }
            }
        }

        HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_SET);
    }
    return 0;
}
