#include "../Inc/matrix_keyboard.h"

#include <stddef.h>
#include <string.h>

static matrix_keyboard_t matrix_keyboard;
static const char chars[MATRIX_KEYBOARD_SIZE][MATRIX_KEYBOARD_SIZE] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'},
};
static bool is_init = false;

bool matrix_keyboard_init (matrix_keyboard_t * matrix_keyboard_in)
{
	if (NULL == matrix_keyboard_in)
		return false;

    for (size_t i = 0; i < MATRIX_KEYBOARD_SIZE; i++)
        if (NULL == matrix_keyboard_in->strs[i].port)
            return false;

    for (size_t i = 0; i < MATRIX_KEYBOARD_SIZE; i++)
        if (NULL == matrix_keyboard_in->cols[i].port)
            return false;

    memcpy (&matrix_keyboard, matrix_keyboard_in, sizeof (matrix_keyboard));

    is_init = true;

    return true;

}

char matrix_keyboard_get_char(void)
{
    if (!is_init) {
        return '\0';
    }

    for (size_t i = 0; i < MATRIX_KEYBOARD_SIZE; i++) {
        HAL_GPIO_WritePin (matrix_keyboard.cols[i].port, matrix_keyboard.cols[i].pin, GPIO_PIN_RESET);
        for (size_t j = 0; j < MATRIX_KEYBOARD_SIZE; j++) {
            if (HAL_GPIO_ReadPin (matrix_keyboard.strs[j].port, matrix_keyboard.strs[j].pin) == GPIO_PIN_RESET) {
            	HAL_GPIO_WritePin (matrix_keyboard.cols[i].port, matrix_keyboard.cols[i].pin, GPIO_PIN_SET);
                return chars[i][j];
            }
        }
        HAL_GPIO_WritePin (matrix_keyboard.cols[i].port, matrix_keyboard.cols[i].pin, GPIO_PIN_SET);
    }

    return '\0';
}
