/*
 * NetSupport.c
 *
 *  Created on: 22-Dec-2020
 *      Author: srinidhi
 */
#include <NetSupport.h>
#include "osapi-os-core.h"
#include <string.h>

/*****************************************************************************
 *
 * Server Function for Stream Network Functional Test
 *
 *****************************************************************************/
void Server_Fn()
{
	int32 LocalConnID, connAlive, i,j;

	LocalConnID = FreeconnId;
	OS_printf("PrintfromTask %d\n", LocalConnID);
	connRelSts[LocalConnID] = Connected;
	ConnInit[LocalConnID] = Done;
	connAlive = 1;
	j=100000;

	while (connAlive)
	{

		/* Recieve incoming data from client*/
		OS_printf("ConnectionID[%d]= %u \n", LocalConnID, (uint32)connsock_id[LocalConnID]);
		OS_TimedRead(connsock_id[LocalConnID], Buf_rcv_s[LocalConnID],
				BufferLen, 100);
			OS_printf("receive buffer: ");
				for (i = 0; i < 20; i++)
			OS_printf("%d ", Buf_rcv_s[LocalConnID][i]);
			OS_printf(": \n");


		if ((Buf_rcv_s[LocalConnID][0]== 9) && (Buf_rcv_s[LocalConnID][1]== 9) )
		{
			//OS_printf("abc received %d\n", LocalConnID);
			//strcpy(Buf_trans[LocalConnID], "Close conn Ack");
			/** OS_printf("send buffer: ");
				for (i = 0; i < 8; i++)
					OS_printf("%c ", Buf_trans[LocalConnID][i]);
				OS_printf(": \n");
			**/
			for (i = 0; i < BufferLen; i++)
									{
							Buf_trans[LocalConnID][i]= 8;
									}
			OS_TimedWrite(connsock_id[LocalConnID], Buf_trans[LocalConnID],
					BufferLen, 100);
			connAlive = 0;
		}
		else
		{
			//OS_printf("xyz received %d\n", LocalConnID);
			/* Transform the incoming data and send it back to client */
			//strcpy(Buf_trans[LocalConnID], "uvw");
			for (i = 0; i < BufferLen; i++)
						{
				Buf_trans[LocalConnID][i]= j;
				j--;
						}
		//	strcpy(Buf_trans[LocalConnID], "ServerTx");
			//strcat(Buf_trans[LocalConnID], Buf_rcv_s[LocalConnID]);
			/** OS_printf("send buffer: ");
				for (i = 0; i < 8; i++)
					OS_printf("%c ", Buf_trans[LocalConnID][i]);
				OS_printf(": \n");
			**/
			OS_TimedWrite(connsock_id[LocalConnID], Buf_trans[LocalConnID],
					BufferLen, 100);

		}
		OS_TaskDelay(5000);
	}

	OS_printf("Connection Closed %d", LocalConnID);
	OS_close(connsock_id[LocalConnID]);
	connRelSts[LocalConnID] = Disconnected;
	OS_TaskExit();

} /* end Server_Fn */

void TCPConnMgmt()
{
	int MaxconnAcc;
	MaxconnAcc = 1;

	while (MaxconnAcc)
	{
		FreeconnId = 0;
		int j;
		activeConnections = 0;

		for (j = 0; j < MAX_CONNECTIONS; j++)
		{
			if ((connRelSts[j] == Disconnected)
					&& (connAllocSts[j] == Allocated)
					&& (ConnInit[j] == Done))
			{
				connAllocSts[j] = Released;
				ConnInit[j] = Pending;
				//snprintf(taskname, sizeof(taskname), "Task %d", tasknum);
				status = OS_TaskDelete(TaskData[j].task_id);
			}
		}

		for (j = 0; j < MAX_CONNECTIONS; j++)
		{
			if (connAllocSts[j] == Allocated)
			{
				activeConnections++;
			}
		}
		OS_printf("No. of Active connections %d\n", activeConnections);
		for (j = 0; j < MAX_CONNECTIONS; j++)
		{
			if (connAllocSts[j] == Released)
			{	//connstsvalid=0;

				FreeconnId = j;
				OS_printf("found free ConnId %d\n", FreeconnId);
				break;	//exit(0);
			}
			OS_printf("finding free Conn %d\n", j);
		}

		if (connAllocSts[FreeconnId] == Released)
		{
			/* Accept incoming connections */
			OS_printf(".");
			status = OS_SocketAccept(serv_socket_id, &connsock_id[FreeconnId],
					&addr[FreeconnId], 5000);
			OS_printf("- ReqConID: %u\n",(uint32)connsock_id[FreeconnId]);
			OS_printf(". SerSocTimeout? %d, %d\n", FreeconnId, status);
			if (status == OS_SUCCESS)
			{
				OS_printf("!!!!Connection Allocated!!! %d\n", FreeconnId);
				OS_printf("ForeSts: %d\n", (int32)connAllocSts[FreeconnId]);
				connAllocSts[FreeconnId] = Allocated;
				OS_printf("AftSts: %d\n", (int32)connAllocSts[FreeconnId]);
				status = OS_TaskCreate(&TaskData[FreeconnId].task_id, SerName[FreeconnId],
						Server_Fn,
						//0,
						TaskData[FreeconnId].task_stack,
						DefaultTask_STACK_SIZE,
						(DefaultTask_PRIORITY+FreeconnId), 0);

				if (status == OS_SUCCESS)
					OS_printf("Network Task to transmit %d\n", FreeconnId);
				else OS_printf("TaskCreateErrorMsg[%d]=%d\n",FreeconnId, status);
			}
			else
			{
				connAllocSts[FreeconnId] = Released;
				OS_printf("!!!!Connection Released!!! %d\n", FreeconnId);
			}
		}
		else
			OS_printf("All the connections are occupied \n");

		OS_TaskDelay(5000);
	}

}

int CreateServerTCPSocket()
{

	/**
	 *  Setting up Server	**/
	serv_socket_id = OS_OBJECT_ID_UNDEFINED;

	status = OS_SocketOpen(&serv_socket_id, OS_SocketDomain_INET,
			OS_SocketType_STREAM);
	if (status == OS_SUCCESS)
		OS_printf("Server Socket Creation successful \n");

	status = OS_SocketAddrInit(&s_addr, OS_SocketDomain_INET);
	if (status == OS_SUCCESS)
		OS_printf("Server Socket Address Set successful \n");

	status = OS_SocketAddrSetPort(&s_addr, 5567);
	if (status == OS_SUCCESS)
		OS_printf("Server Socket Port 5567 Set successful \n");

	status = OS_SocketAddrFromString(&s_addr, "10.21.30.129"); // change to10.21.30.129
	status = OS_SocketBind(serv_socket_id, &s_addr); // Entered Listening state
	if (status == OS_SUCCESS)
		OS_printf("Server Socket Port 10.21.30.129:5567 Bind successful \n");

	int i;
	//connsock_id = OS_OBJECT_ID_UNDEFINED;

	for (i = 0; i < MAX_CONNECTIONS; i++)
	{
		connsock_id[i] = OS_OBJECT_ID_UNDEFINED;
		connAllocSts[i] = Released;
		connRelSts[i] = Disconnected;
		ConnInit[i] = Pending;
		OS_printf("Init Conn %d\n", i);
		snprintf(SerName[i], 8, "Serv %d", i);

	}


	/* Create a server task */
	status = OS_TaskCreate(&s_task_id, "TCPConnMgmt", TCPConnMgmt, 0, 1024, 231,
			0);
	if (status == OS_SUCCESS)
		OS_printf("Task for connection management \n");

	return 0;
}
