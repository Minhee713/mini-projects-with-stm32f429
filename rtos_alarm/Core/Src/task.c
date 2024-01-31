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

enum CLOCK_MODE {
	NORMAL_STATE, TIME_SETTING, ALARM_TIME_SETTING, MUSIC_SELECT
};

enum CLOCK_BUTTON {
	NOTHING, UP, DOWN, RIGHT, LEFT, SELECT
};

struct clock_state {
	enum CLOCK_MODE mode;
	enum CLOCK_BUTTON button;
	int music_num;
};

typedef struct {
	int8_t hours;
	int8_t minutes;
	int8_t seconds;
} TimeTypeDef;

typedef struct {
	uint32_t magic_num;
	TimeTypeDef setting_time;
	TimeTypeDef alarm_time;
	int8_t alarm_music_num;
} NVitemTypeDef;

typedef struct {
	int8_t musicNum;
	char musicTitle[20];
} MusicTypeDef;

struct clock_state current_state;

uint32_t current_time, last_time, interval;
int btn_cnt = 0;

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

void buttonCheck(void);
void selecClockMode(void);


/*Task functions*/
void USER_threads(void)
{
	printf("User threads start!!\n");
	/*lcd_init();
	vTaskDelay(pdMS_TO_TICKS(2000)); // why this doesnt work?*/
	xTaskCreate((TaskFunction_t)TaskMain, "TaskMain", 256, NULL, TASK_MAIN_PRIO, &xHandleMain);
	//xTaskCreate((TaskFunction_t)Task1, "Task1", 256, NULL, TASK_1_PRIO, &xHandle1);

}

void TaskMain(void)
{
	const char* taskMainName = "TaskMain";

	lcd_init();
	vTaskDelay(pdMS_TO_TICKS(2000));

	xTaskCreate((TaskFunction_t)Task1, "Task1", 256, NULL, TASK_1_PRIO, &xHandle1);
	//vTaskDelay(pdMS_TO_TICKS(1000));
	vTaskSuspend(xHandleMain);
	//vTaskResume(xHandleMain);

}

void Task1(void)
{
	const char* task1 = "Task1";

	lcd_test1();
	vTaskDelay(pdMS_TO_TICKS(1000));

	//buttonCheck();
	//selecClockMode();

/*	vTaskSuspend(xHandle1);
	vTaskResume(xHandleMain);*/





}

void buttonCheck(void)
{
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == 0) {
		HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
	}

}


/*void selecClockMode(void)
{
	switch (current_state.mode) {
			case NORMAL_STATE:
				printf("nomal mode\n");
				//get_time();
				break;
			case TIME_SETTING:
				//time_set_mode();
				break;
			case ALARM_TIME_SETTING:
				//alarm_set_mode();
				break;
			case MUSIC_SELECT:
				//music_set_mode();
				break;
			default:
				break;
			}
}*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		if (GPIO_Pin == GPIO_PIN_13) {
			HAL_GPIO_TogglePin(GPIOB, LD3_Pin);

			current_time = xTaskGetTickCount();
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
			}
		}
}



