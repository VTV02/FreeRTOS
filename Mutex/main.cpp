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
//void func_3(void);
//declare variable manage semaphore 
xSemaphoreHandle Sem_Handle;

/*
	configUSE_COUNTING_MUTEXS
	xSemaphoreCreateMutex()
	xSemaphoreGive;
	xSemaphoreTake;
	
*/

int main(void) {
	Sem_Handle = xSemaphoreCreateMutex();//configure couting max = 2. O is has no semaphore intitial 
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	//xTaskCreate(func_3, "TASK_3", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	int a, b;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n%s give semaphore, SEM=1\n", pcTaskGetName(tsk1));
		if (xSemaphoreTake(Sem_Handle, pdMS_TO_TICKS(portMAX_DELAY)))
		{
			//Critical section 
			//--------------------------------------------
			printf("\n%s Accessed\n", pcTaskGetName(tsk1));
			printf("\nTASK 1: Input a,b: ");
			scanf_s("%d %d",&a,&b);
			printf("\nSum %d + %d = %d ", a, b, a + b);
			//--------------------------------------------
			Sleep(2000);
			xSemaphoreGive(Sem_Handle);//SEM=1

		}
		else {
			printf("\n %s Can't access!\n",pcTaskGetName(tsk1));
		}
		vTaskDelay(pdMS_TO_TICKS(2000));
		
	}
}

void func_2(void) {
	TaskHandle_t tsk2;
	int a, b;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		if (xSemaphoreTake(Sem_Handle, pdMS_TO_TICKS(portMAX_DELAY)))
		{
			//Critical section 
			//--------------------------------------------
			printf("\n%s Accessed\n", pcTaskGetName(tsk2));
			printf("\nTASK 2: Input a,b: ");
			scanf_s("%d %d", &a, &b);
			printf("\nSum %d + %d = %d ", a, b, a + b);
			//--------------------------------------------
			Sleep(2000);
			xSemaphoreGive(Sem_Handle);//SEM=1

		}
		else {
			printf("\n %s Can't access!\n", pcTaskGetName(tsk2));
		}
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}
/*void func_3(void) {
	TaskHandle_t tsk3;
	while (1) {
		tsk3 = xTaskGetCurrentTaskHandle();
		//take semaphore with portMAX_DELAY wait until took semaphore <=>BLOCKED!!! If task2 not take 
		xSemaphoreTake(Sem_Handle, portMAX_DELAY);
		xSemaphoreTake(Sem_Handle, portMAX_DELAY);
		printf("%s IS RUNNING..................\n", pcTaskGetName(tsk3));
		//In task2 don't need vTaskDelay 
	}
}*/
