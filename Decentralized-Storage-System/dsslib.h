#include <winsock2.h>
#include <ws2def.h>
#include <pthread.h>


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//  WSADATA
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//	WSADATA variable for init socket
WSADATA* new_wsadata;

//  Alloc memory for WSADATA variable
#define ALLOC_WSADATA(_wsadata) _wsadata = malloc(sizeof(WSADATA))

//  Initiates use of the Winsock DLL by a process.
#define CHECK_WSA_STARTUP(_wsadata) \
do { \
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
#define PTHREAD_CREATE(name_thread, attr_tread, fc_tread, fc_arg_thread) \
do { \
    if (pthread_create(&name_thread, attr_tread, fc_tread, fc_arg_thread) != 0) { \
        printf("DEBUG: threads start failed\n"); \
        return 1; \
    } \
} while (0)

//	Wait for both threads to complete their tasks
#define PYHREAD_JOIN(name_thread, retval) pthread_join(name_thread, retval)

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//  Socket address
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  Initializes receive address (family, port, and IP) using a macro
#define SET_RECEIVE_ADDR(sock_addr, port) \
do { \
    if(port > 0) { \
        (sock_addr).sin_family = AF_INET; \
        (sock_addr).sin_port = htons(port); \
        inet_pton(AF_INET, INADDR_ANY, &sock_addr.sin_addr.S_un.S_addr); \
    } \
    else \
        printf("DEBUG: port is NULL\n"); \
} while (0)