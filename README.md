# Драйвер матричной клавиатуры для STM32F1xx

Драйвер для опроса матричной клавиатуры 4x4 на микроконтроллерах STM32F1xx с использованием HAL библиотеки.

## Возможности
- Инициализация GPIO для строк и столбцов
- Возврат ASCII символа нажатой клавиши
- Поддерживается стандартная раскладка 4x4:
```
1 2 3 A
4 5 6 B
7 8 9 C
* 0 # D
```
- Основан на библиотеке HAL от STMicroelectronics (переделать на LL или CMSIS не составит большего труда)
- Сам драйвер НЕ настраивает необходимые выводы

## Подключение

### Столбцы (Выходы)
| Клавиатура | STM32 | Порт  | Режим          |
|------------|-------|-------|---------------|
| COL1       | PB15  | GPIOB | Output Open-Drain |
| COL2       | PB14  | GPIOB | Output Open-Drain |
| COL3       | PB13  | GPIOB | Output Open-Drain | 
| COL4       | PB12  | GPIOB | Output Open-Drain |

### Строки (Входы)
| Клавиатура | STM32 | Порт  | Режим        |
|------------|-------|-------|-------------|
| ROW1       | PA11  | GPIOA | Input Pull-Up|
| ROW2       | PA10  | GPIOA | Input Pull-Up|
| ROW3       | PA9   | GPIOA | Input Pull-Up|
| ROW4       | PA8   | GPIOA | Input Pull-Up|

## Настройка

Настройте GPIO в gpio.c:
```
 // Настройка столбцов
GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

// Настройка строк  
GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_PULLUP;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
```

## Пример использования

#include "matrix_keyboard.h"
```
int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  matrix_keyboard_t keypad = {
    .cols = {
      {GPIOB, GPIO_PIN_15}, // COL1
      {GPIOB, GPIO_PIN_14}, // COL2 
      {GPIOB, GPIO_PIN_13}, // COL3
      {GPIOB, GPIO_PIN_12}  // COL4
    },
    .strs = {
      {GPIOA, GPIO_PIN_11}, // ROW1
      {GPIOA, GPIO_PIN_10}, // ROW2
      {GPIOA, GPIO_PIN_9},  // ROW3
      {GPIOA, GPIO_PIN_8}   // ROW4  
    }
  };

  if(!matrix_keyboard_init(&keypad)) {
    Error_Handler();
  }

  while(1) {
    char key = matrix_keyboard_get_char();
    if(key != '\0') {
      // Обработка нажатия клавиши
    }
    HAL_Delay(10); // Задержка для защиты от дребезга
  }
}
```
