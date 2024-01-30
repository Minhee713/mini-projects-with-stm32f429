/*
 * task.c
 *
 *  Created on: Jan 23, 2024
 *      Author: 권민희
 */

#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>

/*Task priority*/
#define TASK_MAIN_PRIO 20
#define TASK_1_PRIO	   10
#define TASK_2_PRIO	   9
#define TASK_3_PRIO    8
#define TASK_4_PRIO    7

TaskHandle_t xHandleMain, xHandle1, xHandle2;

void TaskMain(void);
void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);
void Task5(void);



/*Task functions*/
void USER_threads(void)
{
	printf("User threads start!!\n");
	xTaskCreate((TaskFunction_t)TaskMain, "TaskMain", 256, NULL, TASK_MAIN_PRIO, &xHandleMain);
}

void TaskMain(void)
{
	const char* taskMainName = "TaskMain";
	for (;;) {
		printf("%s is running\r\n", taskMainName);
	}
	lcd_init();
	xTaskCreate((TaskFunction_t)Task1, "Task1", 256, NULL, TASK_1_PRIO, &xHandle1);
//	vTaskSuspend(xHandleMain);
	//vTaskResume(xHandleMain);

}

void Task1(void)
{
	const char* task1 = "Task1";
	for (;;) {
		printf("%s is running\r\n", task1);
	}
	lcd_test1();
	vTaskSuspend(xHandle1);

//	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == 1) {
//				HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
//	}



}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		if (GPIO_Pin == GPIO_PIN_13) {
			HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
			vTaskSuspend(xHandleMain);

			/*current_time = HAL_GetTick();
			interval = current_time - last_time;
			last_time = current_time;

			if (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_3) == 1) {
				if (interval < 130) {
					btn_cnt += 3;
				} else if (interval >= 130 && interval < 200) {
					printf("One click!!  interval = %u\r\n",
							(unsigned int) interval);
					btn_cnt = 0;
					current_state.mode = TIME_SETTING;
				} else if (interval >= 300 && interval <= 1000) {
					printf("Long click!!  interval = %u\r\n",
							(unsigned int) interval);
					btn_cnt = 0;
					current_state.mode = ALARM_TIME_SETTING;
				}
				if (btn_cnt >= 5) {
					printf("Double click!!  interval = %u   btn_cnt = %d  \r\n",
							(unsigned int) interval, btn_cnt);
					btn_cnt = 0;
					current_state.mode = MUSIC_SELECT;
				}
			}*/
		}
}



