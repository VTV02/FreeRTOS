# BINARY SEMAPHORE
![image](https://github.com/VTV02/FreeRTOS/assets/93756924/738d5bab-4c90-4592-a8fe-087575f7b576)

Theo như hình trên thì ta có Task2 có độ ưu tiên cao hơn Task1 và hoạt động ở chế độ không độc quyền. Mới đầu vào do có độ ưu tiên cao hơn nên Task 2 sẽ được chạy trước. Tuy nhiên đến hàm để Take semophonre thì lại đợi do lúc này semophore mới khởi tạo và có giá trị là 0 nên Task2 thưc thị xong và nó rơi vào trạng thái <span style="color: red;">BLOCKED!!!</span>
. Lúc này Task1 sẽ chiếm quyền và chạy sau khi chạy xong nó give semaphore lên 1. Lúc này Task2 take và chiếm quyền rồi nó lại tiếp tục take và giá trị lại trở về 0 nên Task2 tiếp tục bị BLOCKED và Task1 được chạy và cứ như thế.


````c
void func_1(void) {
	TaskHandle_t tsk1;
	
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		//trước khi give thì SEM=1
		printf("%s give semaphore, SEM=1\n", pcTaskGetName(tsk1));
		//Sau khi give thì sem=0
		xSemaphoreGive(Sem_Handle);
		printf("%s finish semaphore\n", pcTaskGetName(tsk1));
		//after 1s will be give one SEM.
		vTaskDelay(pdMS_TO_TICKS(1000));
		
	}
}
````

Task1 chạy xong give Sem_Handle bằng cách đưa nó về 0 sau đó nghỉ 1000ms.

````c
void func_2(void) {
	TaskHandle_t tsk2;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		Trước khi take thì sem=0
		//take semaphore with portMAX_DELAY wait until took semaphore <=>BLOCKED!!! If task2 not take 
		xSemaphoreTake(Sem_Handle, portMAX_DELAY);
		//Sau khi take thì sem=1 và task1 chạy, task2 tiếp tục đợi.
		printf("%s synchronzied..................\n", pcTaskGetName(tsk2));
		//In task2 don't need vTaskDelay 
	}
}
````
Sau khi task1 give SEM=1 thì task2 sẽ take ngay. 

<img width="960" alt="image" src="https://github.com/VTV02/FreeRTOS/assets/93756924/c7184dd8-e81d-465a-aa9f-691d12443c9e">
