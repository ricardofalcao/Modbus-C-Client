#ifndef BUFFER_H
#define BUFFER_H 1

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
/*
    Write to byte buffers with big endian
*/

void bufc(char * buffer, char value);

void bufi16(char * buffer, uint16_t value);

#endif