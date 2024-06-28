# Preemptive and Non-Preemptive

<img width="579" alt="Untitled" src="https://github.com/VTV02/FreeRTOS/assets/93756924/69af3401-31e3-49eb-a691-27a3bb4be5ae">


Ta muốn tính toán thì cho sẵn giá trị của a và b hoặc nhập a và b từ bên ngoài task vì hàm scanf là một hàm blocking nó sẽ đợi cho đến khi nào người dùng nhập nên gây vấn đề về thời gian và sự nhường quyền cho task khác mà RTOS thì rất khắc khe việc thời gian. 

## **Non-Preemptive**

<img width="960" alt="Untitled 1" src="https://github.com/VTV02/FreeRTOS/assets/93756924/99ee0b27-33e9-4384-97a1-3fc982d93bde">


Ở chế độ độc quyền mới vào thì task2 có độ ưu tiên cao hơn nhưng ta cho nó ngủ 5s thì lúc này task1 sẽ được chạy nhưng do độc quyên nên task 1 chạy đến hết 5s task2 thức đòi quyên ưu tiên cao để chạy nhưng độc quyền nên task1 vẫn chạy trừ khi ta cho task1 ngủ thì nó mới trả cho task2. 

```cpp
void func_1(void) {
	TaskHandle_t tsk1;
	int a, b;
	a = 10;
	b = 20;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING............................... \n", pcTaskGetName(tsk1));
		printf("Addition %d + %d = %d ", a, b, a + b);

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
```

Đây là chế độ độc quyền nên khi task2 ngủ mặc dù độ ưu tiên cao hơn thì vẫn không được chạy nến task1 đang chạy và không có vTaskDelay. 

<img width="463" alt="Untitled 2" src="https://github.com/VTV02/FreeRTOS/assets/93756924/02193617-24e6-48de-8b83-ab7952c3400d">


## **Preemptive**

<img width="960" alt="Untitled 3" src="https://github.com/VTV02/FreeRTOS/assets/93756924/c8759b4c-a298-428e-91ae-848bc96a0b56">

```cpp
void func_1(void) {
	TaskHandle_t tsk1;
	int a, b;
	a = 10;
	b = 20;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING............................... \n", pcTaskGetName(tsk1));
		printf("Addition %d + %d = %d ", a, b, a + b);
		vTaskDelay(pdMS_TO_TICKS(2000));
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

```

![Untitled 4](https://github.com/VTV02/FreeRTOS/assets/93756924/c53afc35-a298-423a-9231-11048944c0b5)

![Untitled 5](https://github.com/VTV02/FreeRTOS/assets/93756924/d36db1eb-cac6-46a5-a77f-901734b07794)

