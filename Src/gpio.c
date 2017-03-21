#include "gpio.h"
#include "stm32f7xx_hal.h"

void gpio_set_output (GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin) {
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);	
}

void gpio_set_input (GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin) {
	
}

void gpio_all_on(void) {
	
	HAL_GPIO_WritePin (PORT_TR0, PIN_TR0, GPIO_PIN_SET);
	HAL_GPIO_WritePin (PORT_TR1, PIN_TR1, GPIO_PIN_SET);
	HAL_GPIO_WritePin (PORT_TR2, PIN_TR2, GPIO_PIN_SET);
	HAL_GPIO_WritePin (PORT_TR3, PIN_TR3, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin (PORT_ACC0, PIN_ACC0, GPIO_PIN_SET);
	HAL_GPIO_WritePin (PORT_ACC1, PIN_ACC1, GPIO_PIN_SET);
	HAL_GPIO_WritePin (PORT_ACC2, PIN_ACC2, GPIO_PIN_SET);
	HAL_GPIO_WritePin (PORT_ACC3, PIN_ACC3, GPIO_PIN_SET);
}

void gpio_all_off(void) {
	
	HAL_GPIO_WritePin (PORT_TR0, PIN_TR0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (PORT_TR1, PIN_TR1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (PORT_TR2, PIN_TR2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (PORT_TR3, PIN_TR3, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin (PORT_ACC0, PIN_ACC0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (PORT_ACC1, PIN_ACC1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (PORT_ACC2, PIN_ACC2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (PORT_ACC3, PIN_ACC3, GPIO_PIN_RESET);
}

void gpio_init(void) {
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
	
	
	gpio_set_output(PORT_TR0, PIN_TR0);
	gpio_set_output(PORT_TR1, PIN_TR1);
	gpio_set_output(PORT_TR2, PIN_TR2);
	gpio_set_output(PORT_TR3, PIN_TR3);
}
