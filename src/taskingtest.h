/*
 * taskingtest.h
 *
 *  Created on: 22-Dec-2020
 *      Author: srinidhi
 */



#include <stdio.h>
#include "common_types.h"
#include "osapi.h"


/* Task 1 */

#define TASK_1_ID         1
#define TASK_1_STACK_SIZE 1024
#define TASK_1_PRIORITY   101

uint32 task_1_stack[TASK_1_STACK_SIZE];

void task_1(void);


/* Task 2 */

#define TASK_2_ID         2
#define TASK_2_STACK_SIZE 1024
#define TASK_2_PRIORITY   101

uint32 task_2_stack[TASK_2_STACK_SIZE];

void task_2(void);


/* Task 3 */

#define TASK_3_ID         3
#define TASK_3_STACK_SIZE 1024
#define TASK_3_PRIORITY   103

uint32 task_3_stack[TASK_3_STACK_SIZE];

void task_3(void);


/* OS Constructs */

#define MSGQ_ID           1
#define MSGQ_DEPTH        50
#define MSGQ_SIZE         4

#define MUTEX_ID          1

uint32 task_1_id, task_2_id, task_3_id;
int32 Result;
uint32 mutex_id, msgq_id;
uint32 StartInhibit;
uint32 Counter;

/* Global Data */

uint32 shared_resource_x;

void taskinit(void);
void task_1(void);
void task_2(void);
void task_3(void);

