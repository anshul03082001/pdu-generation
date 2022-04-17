/*
 * NetSupport.h
 *
 *  Created on: 22-Dec-2020
 *      Author: srinidhi
 */
#include <stdio.h>
#include <common_types.h>
#include <osapi.h>

#ifndef SRC_NETSUPPORT_H_
#define SRC_NETSUPPORT_H_
#define MAX_CONNECTIONS 3
#define BufferLen 2900

#define DefaultTask_STACK_SIZE 1024
#define DefaultTask_PRIORITY   50

int32 status;
int32 expected, FreeconnId;
uint32 iter;
uint32 loopcnt;
osal_id_t temp_id;
OS_SockAddr_t temp_addr;
OS_task_prop_t taskprop;
osal_id_t serv_socket_id, c_socket_id, s_task_id;

OS_SockAddr_t s_addr, c_addr;
char SerName [MAX_CONNECTIONS][8];
uint32 Buf_rcv_c[MAX_CONNECTIONS][BufferLen],Buf_send_c[MAX_CONNECTIONS][BufferLen],Buf_rcv_trans[MAX_CONNECTIONS][BufferLen],Buf_expec_trans[MAX_CONNECTIONS][BufferLen];

enum eConnStsMang {Allocated = 1, Released=0};
enum eConnStsHandl {Connected=1, Disconnected=0};
enum eConnInitial {Pending=1, Done=0};

enum eConnStsMang connAllocSts [MAX_CONNECTIONS];
enum eConnStsHandl connRelSts [MAX_CONNECTIONS];
enum eConnInitial ConnInit [MAX_CONNECTIONS];
typedef struct
{
    osal_id_t task_id;
    uint32    task_stack[DefaultTask_STACK_SIZE];
} TaskDataStruct;

uint32 activeConnections ;
TaskDataStruct TaskData[MAX_CONNECTIONS];
osal_id_t connsock_id[MAX_CONNECTIONS];
uint32 iter;
OS_SockAddr_t addr[MAX_CONNECTIONS];

char RefStr[8];
uint32 Buf_rcv_s[MAX_CONNECTIONS][BufferLen],Buf_trans[MAX_CONNECTIONS][BufferLen];

void Server_Fn(void);
void TCPConnMgmt(void);
int CreateServerTCPSocket(void);

#endif /* SRC_NETSUPPORT_H_ */
