#include <winsock2.h>
#include <ws2def.h>
#include <pthread.h>


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//  WSADATA
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//  Alloc memory for WSADATA variable
#define ALLOC_WSADATA(_wsadata) _wsadata = malloc(sizeof(WSADATA))

//  Initiates use of the Winsock DLL by a process.
#define CHECK_WSA_STARTUP(_wsadata) do { \
    if (ALLOC_WSADATA(_wsadata)){ \
        if (WSAStartup(MAKEWORD(2, 2), _wsadata) < 0) { \
            printf("DEBUG: Error init winsock\n"); \
            return(1); \
        } \
        free(_wsadata); \
    } \
    else \
        printf("DEBUG: _wsadat is NULL\n"); \
} while (0)


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//  Threads
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	Create threads for sending and receiving data
#define PTHREAD_CREATE(name_thread, attr_tread, fc_tread, fc_arg_thread) do { \
    if (pthread_create(&name_thread, attr_tread, fc_tread, fc_arg_thread) != 0) { \
        printf("DEBUG: threads start failed\n"); \
        return 1; \
    } \
} while (0)

//	Wait for both threads to complete their tasks
#define PYHREAD_JOIN(name_thread, retval) pthread_join(name_thread, retval)