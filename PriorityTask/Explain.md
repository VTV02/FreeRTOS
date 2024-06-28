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

[![Untitled](Ca%CC%82%CC%81u%20tru%CC%81c%20chu%CC%9Bo%CC%9Bng%20tri%CC%80nh%20FreeRTOS%20va%CC%80%20ca%CC%81ch%20ta%CC%A3%201f90812193fb4d1d8e075d0f74dc16d5/Untitled%201.png)](https://www.notion.so/C-u-tr-c-ch-ng-tr-nh-FreeRTOS-v-c-ch-t-o-Task-1f90812193fb4d1d8e075d0f74dc16d5?pvs=4#cc5df164046d4d44afe821c11e0de694)

[![Untitled](Ca%CC%82%CC%81u%20tru%CC%81c%20chu%CC%9Bo%CC%9Bng%20tri%CC%80nh%20FreeRTOS%20va%CC%80%20ca%CC%81ch%20ta%CC%A3%201f90812193fb4d1d8e075d0f74dc16d5/Untitled%202.png)
](https://www.notion.so/C-u-tr-c-ch-ng-tr-nh-FreeRTOS-v-c-ch-t-o-Task-1f90812193fb4d1d8e075d0f74dc16d5?pvs=4#9cfa74953e4949d696a9fa486d4fdd9b)
[![Untitled](Ca%CC%82%CC%81u%20tru%CC%81c%20chu%CC%9Bo%CC%9Bng%20tri%CC%80nh%20FreeRTOS%20va%CC%80%20ca%CC%81ch%20ta%CC%A3%201f90812193fb4d1d8e075d0f74dc16d5/Untitled%203.png)
](https://www.notion.so/C-u-tr-c-ch-ng-tr-nh-FreeRTOS-v-c-ch-t-o-Task-1f90812193fb4d1d8e075d0f74dc16d5?pvs=4#ad81720455e041f09b3f90ab48cb541b)
[![Untitled](Ca%CC%82%CC%81u%20tru%CC%81c%20chu%CC%9Bo%CC%9Bng%20tri%CC%80nh%20FreeRTOS%20va%CC%80%20ca%CC%81ch%20ta%CC%A3%201f90812193fb4d1d8e075d0f74dc16d5/Untitled%204.png)
](https://www.notion.so/C-u-tr-c-ch-ng-tr-nh-FreeRTOS-v-c-ch-t-o-Task-1f90812193fb4d1d8e075d0f74dc16d5?pvs=4#e27195ea874342d58170fb2b176f99a1)
Nếu ta không dùng vTaskDelay cho task1 thì mới đầu mở lên thì task2 sẽ được chạy 1 lần duy nhất sau đó task1 chạy và chạy mãi.
