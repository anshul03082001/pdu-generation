/*
 * taskingtest.c
 *
 *  Created on: 22-Dec-2020
 *      Author: srinidhi
 */

#include<taskingtest.h>


/* ********************** MAIN **************************** */

void taskinit(void) {
	Counter = 0;
	OS_printf(
			"********If You see this, we got into OS_Application_Startup_ TaskingTest->TaskInit****\n");
	OS_QueueCreate(&msgq_id, "MsgQ", MSGQ_DEPTH, MSGQ_SIZE, 0);

	OS_MutSemCreate(&mutex_id, "Mutex", 0);

	StartInhibit = 1;

	/*OS_printf("calling Create Task 1\n");*/
	OS_TaskCreate(&task_1_id, "Task 1", (void*) task_1, task_1_stack,
			TASK_1_STACK_SIZE, TASK_1_PRIORITY, 0);

	/*OS_printf("calling Create Task 2\n");*/
	OS_TaskCreate(&task_2_id, "Task 2", (void*) task_2, task_2_stack,
			TASK_2_STACK_SIZE, TASK_2_PRIORITY, 0);

	/*OS_printf("calling Create Task 3\n");*/
	/*OS_TaskCreate(&task_3_id, "Task 3", (void*) task_3, task_3_stack,
			TASK_3_STACK_SIZE, TASK_3_PRIORITY, 0);*/


}

/* ********************** TASK 1 **************************** */

void task_1(void) {
	OS_time_t CurTime, PastTime;
	OS_printf("In task 1\n");
	OS_TaskRegister();
	uint32 milli_seconds = 1, ticks;
	char host_name[50];
	uint32 name_len = 10;

	//OS_NetworkGetHostName(host_name, name_len);
	//OS_printf("Network ID=%s\n", host_name);

	while (1) {
		if (StartInhibit== 1)
		{
			PastTime = CurTime;
			Result = OS_GetLocalTime(&CurTime);
			OS_printf("T1Diff=%u,  Cus: %u, Pus: %u\t\t %d Cntfrom T1\n",
					CurTime.seconds - PastTime.seconds, CurTime.seconds,
					PastTime.seconds, Counter++);

			/*OS_MutSemTake(mutex_id);

		 shared_resource_x = task_1_id;

		 OS_QueuePut(msgq_id, (void*)&shared_resource_x, sizeof(uint32), 0);

		 shared_resource_x = task_1_id;

		 OS_QueuePut(msgq_id, (void*)&shared_resource_x, sizeof(uint32), 0);

		 OS_MutSemGive(mutex_id);*/

			OS_TaskDelay(100000);

			StartInhibit = 0;
		}
	}
}

/* ********************** TASK 2 **************************** */

void task_2(void) {
	OS_time_t CurTime, PastTime;
	OS_printf("In task 2\n");
	OS_TaskRegister();

	while (1) {
		if (StartInhibit == 0)
		{
			PastTime = CurTime;
			Result = OS_GetLocalTime(&CurTime);
			OS_printf("T2Diff=%u,  Cus: %u, Pus: %u\t\t %d Cntfrom T2\n",
					CurTime.seconds - PastTime.seconds, CurTime.seconds,
					PastTime.seconds, Counter++);
			/*
			 OS_MutSemTake(mutex_id);

			 shared_resource_x = task_2_id;

			 OS_QueuePut(msgq_id, (void*)&shared_resource_x, sizeof(uint32), 0);

			 OS_TaskDelay(150);

			 shared_resource_x = task_2_id;

			 OS_QueuePut(msgq_id, (void*)&shared_resource_x, sizeof(uint32), 0);

			 OS_MutSemGive(mutex_id);*/
			StartInhibit= 1;
		}

		OS_TaskDelay(100000);

	}
}

/* ********************** TASK 3 **************************** */

/*void task_3(void) {

	uint32 data_received;
	uint32 data_size;
	uint32 status;

	OS_TaskRegister();

	while (1) {
		status = OS_QueueGet(msgq_id, (void*) &data_received, MSGQ_SIZE,
				&data_size, OS_PEND);

		if (status == OS_SUCCESS) {
			OS_printf("Received - %d\n", (int )data_received + 1);
		}
	}
}*/
