#include "main.h"
#include "gpio.h"

#define I2C_ADDRESS        0x30F

/* I2C TIMING Register define when I2C clock source is APB1 (SYSCLK/4) */
/* I2C TIMING is calculated in case of the I2C Clock source is the APB1CLK = 50 MHz */
/* This example use TIMING to 0x40912732 to reach 100 kHz speed (Rise time = 700 ns, Fall time = 100 ns) */
#define I2C_TIMING      0x40912732
#define BUFSIZE 3

I2C_HandleTypeDef I2cHandle;
UART_HandleTypeDef UartHandle;
SPI_HandleTypeDef SpiHandle;

uint8_t txBuffer[] = {0x85, 0x55, 0x37};
uint8_t rxBuffer[BUFSIZE];


void SystemClock_Config(void);
static void Error_Handler(void);
static void CPU_CACHE_Enable(void);
uint8_t dd = 0x55;
int cnt = 0;

int main(void)
{
  CPU_CACHE_Enable();
  HAL_Init();
  
  SystemClock_Config();
  //BSP_LED_Init(LED1);
	gpio_init();
  

  /*##-1- Configure the I2C peripheral ######################################*/
  I2cHandle.Instance             = I2Cx;
  I2cHandle.Init.Timing          = I2C_TIMING;
  I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_10BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0xFF;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;  
  
  if(HAL_I2C_Init(&I2cHandle) != HAL_OK) {
    Error_Handler();
  }
  
  HAL_I2CEx_ConfigAnalogFilter(&I2cHandle,I2C_ANALOGFILTER_ENABLE);
	
	
	/*##-1- Configure the SPI peripheral ######################################*/
	SpiHandle.Instance               = SPIx;
  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle.Init.CRCPolynomial     = 7;
  SpiHandle.Init.NSS               = SPI_NSS_SOFT;
	SpiHandle.Init.Mode = SPI_MODE_MASTER;

  if(HAL_SPI_Init(&SpiHandle) != HAL_OK) {
    Error_Handler();
  }

	
	
	/*##-1- Configure the UART peripheral ######################################*/
  UartHandle.Instance        = USARTx;

  UartHandle.Init.BaudRate   = 57600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }  
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }
	
	
	
	
  //while(HAL_I2C_Master_Transmit(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)aTxBuffer, TXBUFFERSIZE, 10000)!= HAL_OK)
  while(1)
  {
		HAL_I2C_Master_Transmit(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)txBuffer, 1, 10000);
		HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t*)txBuffer, (uint8_t *)rxBuffer, BUFSIZE, 5000);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)txBuffer, BUFSIZE, 5000);
		
		if (!cnt) {
			gpio_all_on();
		}
		else {
			gpio_all_off();
		}
		cnt = (cnt+1)%2;
		
  }	    
}

void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Activate the OverDrive to reach the 216 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  if (HAL_I2C_GetError(I2cHandle) != HAL_I2C_ERROR_AF)
  {
    Error_Handler();
  }
}


static void Error_Handler(void)
{
  while(1)
  {    
    BSP_LED_Toggle(LED1); 
    HAL_Delay(1000);
  } 
}

static void CPU_CACHE_Enable(void)
{
  SCB_EnableICache();
  SCB_EnableDCache();
}
