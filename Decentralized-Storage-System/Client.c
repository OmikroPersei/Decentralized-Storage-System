#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "dsslib.h"
#include<windows.h>

//	WSADATA variable for init socket
WSADATA* new_wsadata;

// Thread identifiers: receive_thread - for receiving data.	/	send_thread - for sending data.
pthread_t receive_thread, send_thread;

//	Global variables to hold socket descriptors: reciev_sock - for receiving data.	/	send_sock - for sending data.
int reciev_sock, send_sock;


//	Function for receiving data
void* receive_data(void* arg)
{
	reciev_sock = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (reciev_sock < 0)
	{
		printf("DEBUG: socket creation failed\n");
		return NULL;	//	Return NULL if socket creation fails
	}

	printf("DEBUG: reciev thread start\n");

	return NULL;	//	Return NULL to indicate successful execution
}


//	Function for sending data
void* send_data(void* arg)
{
	send_sock = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (send_sock < 0)
	{
		printf("DEBUG: socket creation failed\n");
		return NULL;	//	Return NULL if socket creation fails
	}

	printf("DEBUG: send thread start\n");

	return NULL;	//	Return NULL to indicate successful execution
}




int main()
{
	//	This macro checks if WSAStartup completed without errors
	CHECK_WSA_STARTUP(new_wsadata);

	//	This macro creates a receive_thread and launches the receive_data function
	PTHREAD_CREATE(receive_thread, NULL, receive_data, NULL);

	//	This macro creates a send_thread and launches the send_data function
	PTHREAD_CREATE(send_thread, NULL, send_data, NULL);



	while (1)
	{
		Sleep(1000);
		printf("DEBUG: Continue\n");
	}

	return 0;// Return 0 to indicate successful execution of the program
}