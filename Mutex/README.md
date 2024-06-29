# PREEMPTIVE MUTEX
MUTEX được phát triển dựa trên Semaphore khá giống với Binary Semaphore nhưng khác ở giá trị SEM mặc định ban đầu.
````cpp
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
````

Cả 2 task đều có cùng mức độ ưu tiên và ở chế độ không độc quyền. Task1 được khởi tạo trước nên sẽ chạy trước. SEM ban đầu là 1 và thỏa điều kiện Take vào thực hiện hàm critical section
trong thời gian thực hiện thì SEM=0 nên task2 bị blocked không chạy được miền găng. Sau khi task1 thực hiện xong nó give lên 1 và ngủ, lúc này task2 mới chạy và tương tự vậy.

<img width="960" alt="image" src="https://github.com/VTV02/FreeRTOS/assets/93756924/22dcb1bb-c956-4873-acbc-d93313b8f2c3">

