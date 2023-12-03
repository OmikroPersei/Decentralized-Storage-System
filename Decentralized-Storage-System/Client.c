#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "WSADATA.h"

// Global variables to hold thread identifiers:
// - receive_thread: Stores the identifier for the thread responsible for receiving data.
// - send_thread: Stores the identifier for the thread responsible for sending data.
pthread_t receive_thread, send_thread;

// Global variables to hold socket descriptors:
// - reciev_sock: Stores the socket descriptor for receiving data.
// - send_sock: Stores the socket descriptor for sending data.
int reciev_sock, send_sock;


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

	//	Create threads for sending and receiving data
	if (pthread_create(&send_thread, NULL, send_data, NULL) != 0 || pthread_create(&receive_thread, NULL, receive_data, NULL) != 0)
	{
		printf("DEBUG: threads start failed\n");
		return 1;	//	Return error code 1 if threads creation fails
	}

	//	Wait for both threads to complete their tasks
	pthread_join(receive_thread, NULL);
	pthread_join(send_thread, NULL);

	printf("DEBUG: Continue\n");

	return 0;// Return 0 to indicate successful execution of the program
}