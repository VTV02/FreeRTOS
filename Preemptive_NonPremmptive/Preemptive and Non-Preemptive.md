# Preemptive and Non-Preemptive

![Untitled](Preemptive%20and%20Non-Preemptive%20c4a0879a06114c909ec5103ae6ccc7c6/Untitled.png)

Ta muốn tính toán thì cho sẵn giá trị của a và b hoặc nhập a và b từ bên ngoài task vì hàm scanf là một hàm blocking nó sẽ đợi cho đến khi nào người dùng nhập nên gây vấn đề về thời gian và sự nhường quyền cho task khác mà RTOS thì rất khắc khe việc thời gian. 

## **Non-Preemptive**

![Untitled](Preemptive%20and%20Non-Preemptive%20c4a0879a06114c909ec5103ae6ccc7c6/Untitled%201.png)

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

![Untitled](Preemptive%20and%20Non-Preemptive%20c4a0879a06114c909ec5103ae6ccc7c6/Untitled%202.png)

## **Preemptive**

![Untitled](Preemptive%20and%20Non-Preemptive%20c4a0879a06114c909ec5103ae6ccc7c6/Untitled%203.png)

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

![Untitled](Preemptive%20and%20Non-Preemptive%20c4a0879a06114c909ec5103ae6ccc7c6/Untitled%204.png)

![Untitled](Preemptive%20and%20Non-Preemptive%20c4a0879a06114c909ec5103ae6ccc7c6/Untitled%205.png)