#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "uart.h"
#include "adc.h"
#include "exti.h"
#include "semphr.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
int sensor_value;
uint8_t btn_state;
void digital_sensor_task(void *pvParameters);
void analog_sensor_task(void *pvParameters);
SemaphoreHandle_t xSerialSemaphore;

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  USART2_UART_RX_Init();
  USART2_UART_TX_Init();



  xSerialSemaphore = xSemaphoreCreateMutex();

  xTaskCreate(digital_sensor_task,"Button Read",256,NULL,1,NULL);
  xTaskCreate(analog_sensor_task,"Sensor Read",256,NULL,1,NULL);

  vTaskStartScheduler();

 while (1)
  {}
}

void digital_sensor_task(void *pvParameters)
{
	gpio_init();
	while(1)
	{
		 btn_state = read_digital_sensor();
		 if(xSemaphoreTake(xSerialSemaphore,(TickType_t)5)==pdTRUE)
		 {
			 printf("The button state is : %d \r\n",btn_state);
			 xSemaphoreGive(xSerialSemaphore);//free semaphore to others.
		 }
		 vTaskDelay(1);
	}

}
void analog_sensor_task(void *pvParameters)
{
	adc_init();
	while(1)
	{
		sensor_value= read_analog_sensor();
		if(xSemaphoreTake(xSerialSemaphore,(TickType_t)5)==pdTRUE)
		{
			printf("The sensor value is : %d \r\n",sensor_value);
			xSemaphoreGive(xSerialSemaphore);//free semaphore to others.
		}
		vTaskDelay(1);
	}
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{

  __HAL_RCC_GPIOA_CLK_ENABLE();


}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }

}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

