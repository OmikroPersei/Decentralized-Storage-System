#include <winsock2.h>
#include <ws2def.h>

WSADATA* new_wsadata;

#define ALLOC_WSADATA(_wsadata) _wsadata = malloc(sizeof(WSADATA))
#define CHECK_WSA_STARTUP(_wsadata) do { \
    if(ALLOC_WSADATA(_wsadata)){ \
        if (WSAStartup(MAKEWORD(2, 2), _wsadata) < 0) { \
            printf("DEBUG: Error init winsock\n"); \
            return(1); \
        } \
        free(_wsadata); \
    } \
    else \
        printf("DEBUG: _wsadat is NULL\n"); \
} while(0)





