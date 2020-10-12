#include "buffer/buffer.h"

void bufc(char * buffer, char value) {
    buffer[0] = value;
}

void bufi16(char * buffer, uint16_t value) {
    value = htons(value);

    memcpy(buffer, &value, sizeof(value));
}