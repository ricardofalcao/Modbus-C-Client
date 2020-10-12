#include <stdio.h>
#include "modbus/transport/transport.h"

#include "modbus/transport/tcp/transport_tcp.h"

void write(const void * buffer, size_t length) {
    printf("write: ");

    for (int i = 0; i < length; i++) {
        printf("%02x ", ((char *) buffer)[i]);
    }

    printf("\n");

    #if TRANSPORT_TYPE == TT_TCP
        write_tcp(buffer, length);
    #endif
}

size_t receive(void * buffer) {
    #if TRANSPORT_TYPE == TT_TCP
        return receive_tcp(buffer);
    #endif
}