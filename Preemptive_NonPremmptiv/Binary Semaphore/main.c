#include <stdio.h>
#include <conio.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
/* 
	when give semaphore Sem_Handle = 1. It means giving up authority to another task
	when take semaphore Sem_Handle = 1. It means receiving permissions from another task. After Took, Sem_Handle will be set to 0
*/

void func_1(void);
void func_2(void);
//declare variable manage semaphore 
xSemaphoreHandle Sem_Handle;

int main(void) {
	Sem_Handle = xSemaphoreCreateBinary();
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("%s give semaphore, SEM=1\n", pcTaskGetName(tsk1));
		xSemaphoreGive(Sem_Handle);//SEM=1
		printf("%s finish semaphore\n", pcTaskGetName(tsk1));
		//after 1s will be give one SEM.
		vTaskDelay(pdMS_TO_TICKS(1000));
		
	}
}

void func_2(void) {
	TaskHandle_t tsk2;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		//take semaphore with portMAX_DELAY wait until took semaphore <=>BLOCKED!!! If task2 not take 
		xSemaphoreTake(Sem_Handle, portMAX_DELAY);

		printf("%s synchronzied..................\n", pcTaskGetName(tsk2));
		//In task2 don't need vTaskDelay 
	}
}
