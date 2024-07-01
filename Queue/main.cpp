#include <stdio.h>
#include <conio.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"



/*
	xQueueCreate()
	xQueueSend()
	xQueueReceive()
*/



void func_1(void);
void func_2(void);
xQueueHandle Queue_Handle;

int main(void) {
	//tao queue 5 phan tu moi phan tu kieu int
	Queue_Handle = xQueueCreate(5, sizeof(int));
	xTaskCreate(func_1,"TASK_1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(func_2,"TASK_2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	int data = 1;
	while (1)
	{
		if (xQueueSend(Queue_Handle, &data, portMAX_DELAY) == pdPASS)
		{
			printf("Send data: %d - Free: %d\n", data, uxQueueSpacesAvailable(Queue_Handle));
			++data;
			
		}
		else {
			printf("Faild to send to queue\n");
			printf("TASK1: Do other task from here.....\n");
		}
		
	}

}

void func_2(void)
{
	int rx = 0;
	while (1)
	{
		if (xQueueReceive(Queue_Handle, &rx, pdMS_TO_TICKS(500)) == pdPASS)
		{
			printf("Receive data: %d - Free: %d \n", rx, uxQueueSpacesAvailable(Queue_Handle));
			//vTaskDelay(pdMS_TO_TICKS(10));
		}
		else
		{
			printf("Failed to receive data from queue\n");
		}

		
	}

}
