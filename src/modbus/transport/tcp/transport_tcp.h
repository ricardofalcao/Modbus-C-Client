#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "modbus/common/types.h"

#define TCP_DEBUG 0

#define TCP_HOST "127.0.0.1"
#define TCP_PORT 502

#define TCP_HEADER_LENGTH 7

#define TCP_MODBUS_PROTOCOL (uint16_t) 0


uint8_t _assert_connection();

void write_tcp(const void * buffer, size_t length);

size_t receive_tcp(char * buffer);