#include "modbus/transport/tcp/transport_tcp.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "buffer/buffer.h"
#include "utils/utils.h"

int socket_id;
uint8_t socket_initialized = 0;

//

uint16_t transaction_id = 1;

uint8_t _assert_connection() {
    if(socket_initialized) {
        return 1;
    }

    socket_id = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(TCP_PORT);
    inet_aton(TCP_HOST, &addr.sin_addr);

    if(connect(socket_id, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
        printf("Could not connect to %s:%d\n", TCP_HOST, TCP_PORT);
        return 0;
    }

    socket_initialized = 1;

    printf("Initialized socket for %s:%d\n", TCP_HOST, TCP_PORT);
    return 1;
}

void write_tcp(const void * _buffer, size_t length) {
    if(!_assert_connection()) {
        return;
    }

    transaction_id++;

    uint16_t total_length = length + TCP_HEADER_LENGTH;

    char * buffer = (char * ) malloc(sizeof(char) * total_length);
    
    bufi16(buffer, transaction_id);
    bufi16(&buffer[2], TCP_MODBUS_PROTOCOL);
    bufi16(&buffer[4], length + 1);
    bufc(&buffer[6], 0x01);
    memcpy(&buffer[7], _buffer, length);

    #ifdef TCP_DEBUG
    print_char_array("write_tcp", buffer, total_length);
    #endif

    send(socket_id, buffer, total_length, 0);
    free(buffer);
}

char tcp_read_buffer[256];
int tcp_read_buffer_length = 0;

size_t receive_tcp(char * buffer) {
    if(!_assert_connection()) {
        return 0;
    }

    int size = recv(socket_id, &tcp_read_buffer[tcp_read_buffer_length], 256 - tcp_read_buffer_length, 0);
    tcp_read_buffer_length += size;

    if(tcp_read_buffer_length < TCP_HEADER_LENGTH) {
        return 0;
    }

    uint16_t transaction_id;
    memcpy(&transaction_id, tcp_read_buffer, sizeof(transaction_id));
    transaction_id = ntohs(transaction_id);

    uint16_t protocol;
    memcpy(&protocol, &tcp_read_buffer[2], sizeof(protocol));
    protocol = ntohs(protocol);

    uint16_t frame_len;
    memcpy(&frame_len, &tcp_read_buffer[4], sizeof(frame_len));
    frame_len = ntohs(frame_len);
;
    if (tcp_read_buffer_length < TCP_HEADER_LENGTH + frame_len - 1) {
        return 0;
    }

    // uint8_t uid = (uint8_t) tcp_read_buffer[6];
    memcpy(buffer, &tcp_read_buffer[7], frame_len - 1);

    #ifdef TCP_DEBUG
    print_char_array("read_tcp", tcp_read_buffer, TCP_HEADER_LENGTH + frame_len - 1);
    #endif

    // shifting buffer
    int total_length = (frame_len - 1) + TCP_HEADER_LENGTH;
    for(int i = total_length; i < tcp_read_buffer_length; i++) {
        tcp_read_buffer[i - total_length] = tcp_read_buffer[i];
    }
    tcp_read_buffer_length -= total_length;

    return frame_len - 1;
}