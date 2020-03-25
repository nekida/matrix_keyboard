#include "matrix_keyboard.h"
#include "main.h"

char get_symbol(void)
{
	GPIO_TypeDef * array_ports_out[] = {mkey_out_4_GPIO_Port, mkey_out_3_GPIO_Port, mkey_out_2_GPIO_Port, mkey_out_1_GPIO_Port};
	uint16_t array_pins_out[] = {mkey_out_4_Pin, mkey_out_3_Pin, mkey_out_2_Pin, mkey_out_1_Pin};
	
	GPIO_TypeDef * array_ports_in[] = {mkey_in_4_GPIO_Port, mkey_in_3_GPIO_Port, mkey_in_2_GPIO_Port, mkey_in_1_GPIO_Port};
	uint16_t array_pins_in[] = {mkey_in_4_Pin, mkey_in_3_Pin, mkey_in_2_Pin, mkey_in_1_Pin};
	
	char chars[] = {'1', '2', '3', 'A',
									'4', '5', '6', 'B',
									'7', '8', '9', 'C',
									'*', '0', '#', 'D'};
	uint8_t cnt = 0;
	uint8_t index = 0;
	uint8_t i, j;
									
	for(i = 0; i < 4; i++)
	{
		HAL_GPIO_WritePin(array_ports_out[i], array_pins_out[i], GPIO_PIN_SET);
		for(j = 0; j < 4; j++)
		{
			cnt++;
			if(HAL_GPIO_ReadPin(array_ports_in[j], array_pins_in[j]))
			{
				index = cnt;
			}		
		}
		HAL_GPIO_WritePin(array_ports_out[i], array_pins_out[i], GPIO_PIN_RESET);
	}
	cnt = 0;
	
	return (index) ? chars[index-1] : '\0';
}
