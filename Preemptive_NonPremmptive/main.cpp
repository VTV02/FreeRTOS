#include <stdio.h>
#include <conio.h>
#include<stdint.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

void func_1(void);
void func_2(void);

int main(void) {
	xTaskCreate(func_1, "Lao Hac", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	int a, b;
	a = 10;
	b = 20;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING............................... \n", pcTaskGetName(tsk1));
		printf("Addition %d + %d = %d ", a, b, a + b);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	
}

void func_2(void) {
	TaskHandle_t tsk2;
	vTaskDelay(pdMS_TO_TICKS(5000));
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING.............................. \n", pcTaskGetName(tsk2));
	}
	
}
