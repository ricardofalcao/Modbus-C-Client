#include "modbus/common/functions/functions.h"

#include <stdlib.h>

char read_buffer[256];

size_t read_response(char _code) {
    size_t length = receive(read_buffer);
    if(length <= 0) {
        return 0;
    }

    char code = (char) read_buffer[0];
    uint8_t is_exception = FC_IS_EXCEPTION(code);
    if (is_exception) {
        printf("Received exception when sending a %02x request.", code);
        return 0;
    }

    code = FC_GET(code);
    if(code != _code) {
        printf("Received response for %02x whilst expecting %02x.", code, _code);
        return 0;
    }

    return length;
}

uint8_t * read_bits(uint16_t * count) {
    uint8_t * coils = (uint8_t *) calloc(*count, sizeof(uint8_t));

    uint8_t byteCount = (uint8_t) read_buffer[1];

    uint8_t coilIndex = 0;
    for(uint8_t i = 0; i < byteCount; i++) {
        char _byte = read_buffer[2 + i]; 
        for(uint8_t bit = 0; bit < 8 && coilIndex < *count; bit++) {
            coils[coilIndex++] = _byte & (1 << bit) ? 1 : 0;
        }
    }

    return coils;
}

uint16_t * read_words(uint16_t * count) {
    uint8_t byteCount = (uint8_t) read_buffer[1];

    *count = byteCount >> 1;
    uint16_t * words = (uint16_t *) calloc(*count, sizeof(uint16_t));

    for(uint8_t i = 0; i < byteCount; i++) {
        uint16_t num; 
        memcpy(&num, &read_buffer[2 + i * 2], sizeof(num));
        words[i] = ntohs(num);
    }

    return words;
}