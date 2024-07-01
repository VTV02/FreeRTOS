# PREEMPTIVE QUEUE TASK1, TASK1 PRIORITY = 1
````cpp
    void func_1(void);
void func_2(void);
xQueueHandle Queue_Handle;

int main(void) {
	//tao queue 5 phan tu moi phan tu kieu int
	Queue_Handle = xQueueCreate(5, sizeof(char));
	xTaskCreate(func_1,"TASK_1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
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
			//Sleep(100);
		}
		else {
			printf("Faild to send to queue\n");
		}
		printf("TASK1: Do other task from here.....\n");
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

		}
		else
		{
			printf("Failed to receive data from queue\n");
		}
	}

}
````
![alt text](image.png)
Trong trường hợp 2 task có độ ưu tiên như nhau và không độc quyền thì task1 được thực thi trước nó gửi hết data vào queue lúc này free là 0 và task1 bị blocked. Task2 lấy hết data ra và bị blocked lúc này free là 5 nên Task1 dậy và gửi đầy vào đấy.

# PREEMPTIVE QUEUE TASK1 HAS PRIORITY = 1, TASK2 HAS PRIORITY = 2

````cpp
    int main(void) {
	//tao queue 5 phan tu moi phan tu kieu int
	Queue_Handle = xQueueCreate(5, sizeof(int));
	xTaskCreate(func_1,"TASK_1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(func_2,"TASK_2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
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
			vTaskDelay(pdMS_TO_TICKS(10));
		}
		else
		{
			printf("Failed to receive data from queue\n");
		}

		
	}

}
````  
![alt text](image-1.png)

Do task2 có độ ưu tiên cao hơn thì mới đầu vào task2 nhưng đang empty nên task2 bị khóa và task1 dậy gửi  1 và task2 dậy phát hiện có 1 và lấy sau đó tiếp tục ngủ. Lúc này task1 mới in được chữ send 1 free 5 của lần gửi trước mà bị task2 cắt ngang. Vì lần này là vTaskDelay nên task2 sẽ ngủ 1000ms lúc này task1 vừa kịp gửi hết và bị blocked và task2 thức dậy lấy 1 rồi bị blocked chưa kịp xài hàm vTaskDelay và task1  gửi 1 và bị blocked.

# PREEMPTIVE QUEUE TASK1 HAS PRIORITY = 2, TASK2 HAS PRIORITY = 1

````cpp
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

````

![alt text](image-2.png)

Do task1 ưu tiên cao hơn thì nó gửi hết xong bị blocked lúc này task2 vừa vô queue lấy ra 1 thì lúc này queue trống 1 và task2 chưa kịp in ra printf thì bị task2 lấy vì trống 1 và task1 lại gửi 6 và free 0 bị blocked tiếp  sau đó task2 mới printf được là receive 1 free 0.

# PREEMPTIVE QUEUE TASK1 HAS PRIORITY = 1, TASK2 HAS PRIORITY = 2 DON'T USE vTaskDelay()

![alt text](image-3.png)

Mới đầu vào Task2 có độ ưu tiên cao hơn nó sẽ vào Queue lấy tuy nhiên Queue lúc này trống nên nó bị blocked và Task1 sẽ chiếm quyền chạy khi mới đưa 1 data vào chưa kịp printf thì Task2 dậy và lấy data ra. Nên ta mới thấy là Receive 1 và free 5 tới lần kế tiếp Task 1 mới có thể in ra là Send data 1 và free 5.