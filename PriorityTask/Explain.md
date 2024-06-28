# Cấu trúc chương trình FreeRTOS và cách tạo Task

TRONG FreeRTOS số càng nhỏ ưu tiên càng cao. 

Trong visual studio Số càng lớn thì độ ưu tiên càng cao.

Khi task được khởi chạy thi nó sẽ vào hàm func_1 để thực thi 

Tham số thứ 2 là tên của task

tham số cuối là kích thước của vùng nhớ stack để nó chuyển đổi task để nó lưu lại trạng thía của nó 

Số 2 là mức độ ưu tiên 

Nội dung của task mình muốn viết gì viết tùy thôi 

TaskHandle_t biến này sẽ chưa những thông tin liên quan đến task 

lấy thông tin của task hiện tại gán cho task1 

**`TaskHandle_t`**:

- Đây là một kiểu dữ liệu định nghĩa trong FreeRTOS để lưu trữ thông tin về một task.
- Một handle (tay cầm) là một con trỏ hoặc một biến tham chiếu dùng để nhận diện một đối tượng (trong trường hợp này là một task) mà FreeRTOS quản lý.
- Kiểu dữ liệu `TaskHandle_t` thường được sử dụng để lưu trữ và thao tác với các task trong các hàm FreeRTOS.

Visual 2022 thì không cần thêm *trong void nó tự hiểu là con trỏ null 

```cpp
int main(void) {
	xTaskCreate(func_1, "Lao Hac", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk1));
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	
}

void func_2(void) {
	TaskHandle_t tsk2;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk2));
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	
}

```

Do Task2 có độ ưu tiên cao hơn nên khi vào nó sẽ chạy task2 trước. Do đây cũng là chế độ PREEMPTION(Không độc quyền) nên khi nó chạy xong gặp lệnh vTaskDelay thì nó sẽ ngủ 10ms →1 tick trong khi này thì task1 sẽ được đưa lên chạy và đến khi hết 1 tick thì task2 sẽ đòi lại chạy cứ như thế.

Nếu ko dùng hàm vTaskDelay cho task1 thì task1 sẽ không nhường quyền cho ai hết vì nó ở vòng lặp while nên nó sẽ chạy mãi. 
<img width="150" alt="Untitled 1" src="https://github.com/VTV02/FreeRTOS/assets/93756924/6056dc38-4e3f-43ba-a201-b229bab3896e">


<img width="622" alt="Untitled 2" src="https://github.com/VTV02/FreeRTOS/assets/93756924/94de016a-bf93-4e76-8b50-f8aef3a38a92">


<img width="664" alt="Untitled 3" src="https://github.com/VTV02/FreeRTOS/assets/93756924/8c3576fe-2f14-423e-95ef-ad84ea391f61">
<img width="381" alt="Untitled 4" src="https://github.com/VTV02/FreeRTOS/assets/93756924/63e85cb8-2bf6-4ccf-ab66-8080019f2413">

Nếu ta không dùng vTaskDelay cho task1 thì mới đầu mở lên thì task2 sẽ được chạy 1 lần duy nhất sau đó task1 chạy và chạy mãi.
