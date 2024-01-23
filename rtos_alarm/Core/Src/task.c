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

/*Task functions*/

void USER_threads(void)
{
	printf("User threads start!!\n");
	xTaskCreate((TaskFunction_t)TaskMain, "TaskMain", 256, NULL, TASK_MAIN_PRIO, &xHandleMain);
}

void TaskMain(void)
{
	const char* taskMainName = "TaskMain";

	printf("%s is running\r\n", taskMainName);
}


