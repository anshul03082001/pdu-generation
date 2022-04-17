#include<myprinter.h>
#include<osapi.h>
#include<taskingtest.h>
#include<NetSupport.h>
//int main(int argc, char *argv[]) 
void OS_Application_Startup()
	{
	//char String[30];
	int Status;
	Status = OS_API_Init();
	printf("Status of API Init = %d", Status);
	OS_printf_enable();
	//printFunct();

	OS_printf("\n\n!! OSAL Startup!!\n\n");
	//return 0;

	taskinit();


	}


void OS_Application_Run()
	{
	//char String[30];

	//printFunct();
	OS_printf_enable();
	OS_printf("\n\n!!OSAL Run!!\n\n");
	
	printFunct();
	CreateServerTCPSocket();
	while(1);
	//return 0;
	}



