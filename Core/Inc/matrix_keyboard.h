#ifndef MATRIX_KEYBOARD_H
#define MATRIX_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"

#define MATRIX_KEYBOARD_SIZE (4)

typedef struct pin_s {
	GPIO_TypeDef *port;
	uint32_t pin;
} pin_t;

typedef struct matrix_keyboard_s {
	pin_t strs[MATRIX_KEYBOARD_SIZE];
	pin_t cols[MATRIX_KEYBOARD_SIZE];
} matrix_keyboard_t;

bool matrix_keyboard_init (matrix_keyboard_t * matrix_keyboard_in);
char matrix_keyboard_get_char (void);

#endif // MATRIX_KEYBOARD_H
