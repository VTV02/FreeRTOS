# Preemptive and Non-Preemptive

<img width="579" alt="Untitled" src="https://github.com/VTV02/FreeRTOS/assets/93756924/69af3401-31e3-49eb-a691-27a3bb4be5ae">


Ta muốn tính toán thì cho sẵn giá trị của a và b hoặc nhập a và b từ bên ngoài task vì hàm scanf là một hàm blocking nó sẽ đợi cho đến khi nào người dùng nhập nên gây vấn đề về thời gian và sự nhường quyền cho task khác mà RTOS thì rất khắc khe việc thời gian. 

## **Non-Preemptive**

<img width="960" alt="Untitled 1" src="https://github.com/VTV02/FreeRTOS/assets/93756924/99ee0b27-33e9-4384-97a1-3fc982d93bde">

```cpp
int main(void) {
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 4, NULL);

	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING............................... \n", pcTaskGetName(tsk1));
		Sleep(1000);
		
	}
}

void func_2(void) {
	TaskHandle_t tsk2;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING.............................. \n", pcTaskGetName(tsk2));
		Sleep(1000);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
```
<img width="950" alt="image" src="https://github.com/VTV02/FreeRTOS/assets/93756924/7bd36da9-c6d3-41f2-bb08-1190d8560842">

Đây là chế độ độc quyền và dựa trên độ ưu tiên nên khi task2 ngủ mặc dù độ ưu tiên cao hơn thì vẫn không được chạy lúc này Task1 sẽ chạy đến khi task 2 ngủ xong 10ms thì nó sẽ thức dậy và đòi quyền chạy lúc này task1 vẫn tiếp tục chạy do độc quyền nếu không có vTaskDelay trong task1.
->Hiểu đơn giản anh đòi là chuyện của anh tôi ngủ anh mới được lấy. Còn không ngủ thì never được lấy.

<img width="463" alt="Untitled 2" src="https://github.com/VTV02/FreeRTOS/assets/93756924/02193617-24e6-48de-8b83-ab7952c3400d">


## **Preemptive**

<img width="960" alt="Untitled 3" src="https://github.com/VTV02/FreeRTOS/assets/93756924/c8759b4c-a298-428e-91ae-848bc96a0b56">

```cpp
int main(void) {
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 4, NULL);

	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING............................... \n", pcTaskGetName(tsk1));
		Sleep(100);
		
	}
}

void func_2(void) {
	TaskHandle_t tsk2;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING.............................. \n", pcTaskGetName(tsk2));
		Sleep(100);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

```
Do là không độc quyền và task2 có ưu tiên cao hơn nên khi nó chạy xong rồi ngủ 10ms thì task1 chạy. Chạy xong task2 sau 10ms tỉnh giấc và đòi lại chạy.
<img width="960" alt="image" src="https://github.com/VTV02/FreeRTOS/assets/93756924/babe0fa0-1343-4d49-9a24-7f6a5b9abebd">
## **Preemptive Priority Equal** ##
```` cpp
	int main(void) {
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING............................... \n", pcTaskGetName(tsk1));
		Sleep(100);
		
	}
}

void func_2(void) {
	TaskHandle_t tsk2;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING.............................. \n", pcTaskGetName(tsk2));
		Sleep(100);
		//vTaskDelay(pdMS_TO_TICKS(10));
	}
}
````
Trường hợp độ ưu tiên bằng nhau thì chạy theo Round Robin.
<img width="953" alt="image" src="https://github.com/VTV02/FreeRTOS/assets/93756924/8f4b7174-2ce6-47da-a9a0-8f51582b9013">
