#include <stdio.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

void func_1(void);
void func_2(void);

//TaskHandle_t TASK_1 = NULL;
//TaskHandle_t TASK_2 = NULL;

int main(void) {
  //Create task with task function,name task, minimum stack, none parameter, priority 2-3, none retunr hanlde
	xTaskCreate(func_1, "Lao Hac", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
  //start scheduler
	vTaskStartScheduler();
  //for loop for infinity 
	for (;;);
}

void func_1(void) {
  //Delecare tsk1 with user data type TaskHandle_t
	TaskHandle_t tsk1;
	while (1) {
    //assign tsk1 euqal current task handle
		tsk1 = xTaskGetCurrentTaskHandle();
		int msTotick = pdMS_TO_TICKS(10);
		printf("\n %s IS RUNNING............................... \n", pcTaskGetName(tsk1));
		printf("      10ms = %d\n", msTotick);
    //sleep 2000ms ->200 tick
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
	
}

void func_2(void) {
	TaskHandle_t tsk2;
	
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING.............................. \n", pcTaskGetName(tsk2));
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
	
}
