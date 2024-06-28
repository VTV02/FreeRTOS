# Preemptive and Non-Preemptive

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/77e65276-0df9-483d-acb1-a8b1793896bc/073dc359-76c3-45a3-b87d-59863315a977/Untitled.png)

Ta muốn tính toán thì cho sẵn giá trị của a và b hoặc nhập a và b từ bên ngoài task vì hàm scanf là một hàm blocking nó sẽ đợi cho đến khi nào người dùng nhập nên gây vấn đề về thời gian và sự nhường quyền cho task khác mà RTOS thì rất khắc khe việc thời gian. 

## **Non-Preemptive**

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/77e65276-0df9-483d-acb1-a8b1793896bc/ddb81a37-14fa-4b77-b095-4b6ddebc4a03/Untitled.png)

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

!![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/77e65276-0df9-483d-acb1-a8b1793896bc/84eb3b59-1305-4c73-9033-7763ba410475/Untitled.png)

## **Preemptive**

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/77e65276-0df9-483d-acb1-a8b1793896bc/05ba9696-fd96-446f-8f27-b688763f77e6/Untitled.png)

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

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/77e65276-0df9-483d-acb1-a8b1793896bc/2f03494b-0da4-4aa0-a07e-889972a3569b/Untitled.png)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/77e65276-0df9-483d-acb1-a8b1793896bc/714e1d3c-170a-46ff-a33c-33712349aea4/Untitled.png)
