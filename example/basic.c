/* USER CODE BEGIN Includes */
#include "keypad.h"
/* USER CODE END Includes */



/* USER CODE BEGIN 2 */
GPIO_TypeDef* rowPorts[ROW_NUM] = {GPIOD, GPIOD, GPIOD, GPIOD};
uint16_t rowPins[ROW_NUM] = {row1_Pin, row2_Pin, row3_Pin, row4_Pin};

GPIO_TypeDef* colPorts[COL_NUM] = {GPIOC, GPIOC, GPIOC, GPIOC};
uint16_t colPins[COL_NUM] = {col1_Pin, col2_Pin, col3_Pin, col4_Pin};

Keypad_SetRowPins(rowPorts, rowPins);
Keypad_SetColPins(colPorts, colPins);
Keypad_Init();
/* USER CODE END 2 */



/* USER CODE BEGIN WHILE */
while (1)
{
    char key = Keypad_Scan();
    if (key) {
        HAL_UART_Transmit(&huart3, (uint8_t*)&key, 1, 100);
    }
    HAL_Delay(100);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}