#ifndef TRANSPORT_H
#define TRANSPORT_H 1

#include <stddef.h>

#include "modbus/common/types.h"

#define TT_TCP 0
#define TRANSPORT_TYPE TT_TCP

void write(const void * buffer, size_t length); 

size_t receive(void * buffer);

#endif