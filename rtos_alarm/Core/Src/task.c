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

#define LCD_ADDR (0x27 << 1)

static void MX_RTC_Init(void);

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

char showTime[30] = { 0 };
char ampm[2][3] = { "AM", "PM" };
char timeStr[30];
char temp_time_buf[30];

RTC_TimeTypeDef RTC_Time;
RTC_DateTypeDef sDate;

RTC_HandleTypeDef hrtc;

/*Task priority*/
#define TASK_MAIN_PRIO 20
#define TASK_1_PRIO	   10
#define TASK_2_PRIO	   9
#define TASK_3_PRIO    8
#define TASK_4_PRIO    7

TaskHandle_t xHandleMain, xHandle1, xHandle2;

void TaskMain(void);
void TaskShowCurrentTime(void);
void TaskbuttonCheck(void);
void Task3(void);
void Task4(void);
void Task5(void);

void buttonCheck(void);
void selecClockMode(void);

/*Task functions*/
void USER_threads(void) {
	printf("User threads start!!\n");
	/*lcd_init();
	 vTaskDelay(pdMS_TO_TICKS(2000)); // why this doesnt work?*/
	xTaskCreate((TaskFunction_t) TaskMain, "TaskMain", 256, NULL,
			TASK_4_PRIO, &xHandleMain);
	//xTaskCreate((TaskFunction_t)Task1, "Task1", 256, NULL, TASK_1_PRIO, &xHandle1);
}

void TaskMain(void) {
	const char *taskMainName = "TaskMain";
	printf("%s start\n", taskMainName);

	MX_RTC_Init();

	lcd_init();
	vTaskDelay(pdMS_TO_TICKS(2000));
	xTaskCreate((TaskFunction_t) TaskShowCurrentTime, "TaskShowCurrentTime", 256, NULL, TASK_1_PRIO,
			&xHandle1);
	vTaskSuspend(xHandleMain);
}

void TaskShowCurrentTime(void) {
	const char *task1 = "TaskShowCurrentTime";
	printf("%s start\n", task1);


	while (1) {
		get_time();
		showCurrentTime();
		printf("test\n");
		xTaskCreate((TaskFunction_t) TaskbuttonCheck, "TaskbuttonCheck", 256, NULL, TASK_2_PRIO,
				&xHandle2);
		vTaskSuspend(xHandle1);
		//buttonCheck();
	}

}

void TaskbuttonCheck(void) {
	printf("button check!!\n");

	buttonCheck();
}

void get_time(void) {
	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	sprintf((char*) temp_time_buf, "%s %02d: %02d: %02d  ",
			ampm[RTC_Time.TimeFormat], RTC_Time.Hours, RTC_Time.Minutes,
			RTC_Time.Seconds);
//	showCurrentTime();
}

void showCurrentTime() {
	LCD_SendCommand(LCD_ADDR, 0b10000000);
	LCD_SendString(LCD_ADDR, "Current Time ");

	LCD_SendCommand(LCD_ADDR, 0b11000000);
	LCD_SendString(LCD_ADDR, temp_time_buf);
}

void buttonCheck(void) {
	if (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13)) {
		HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
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

static void MX_RTC_Init(void) {

	/*USER CODE BEGIN RTC_Init 0*/

	/*USER CODE END RTC_Init 0*/

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	/*USER CODE BEGIN RTC_Init 1*/

	/*USER CODE END RTC_Init 1*/

	/*Initialize RTC Only*/

	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = 0x0;
	sTime.Minutes = 0x0;
	sTime.Seconds = 0x0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 0x1;
	sDate.Year = 0x0;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

