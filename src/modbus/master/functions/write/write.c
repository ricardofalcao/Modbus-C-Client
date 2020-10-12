#include "write.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "buffer/buffer.h"

void master_write_single_coil(m_reg_address address, uint8_t value, read_bit_callback callback) {
    char buffer[5];

    bufc(buffer, FC_WRITE_SINGLE_COIL);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], value ? 0xFF00 : 0x00);

    write(buffer, sizeof(buffer));

    read_response(FC_WRITE_SINGLE_COIL);

    uint16_t count = 1;
    uint8_t * coils = read_bits(&count);
    
    if(callback != NULL) {
        callback(coils[0]);
    }

    free(coils);
}

void master_write_multiple_coils(m_reg_address address, uint8_t * value, uint16_t count, read_bits_callback callback) {
    uint8_t bytes = (uint8_t) ceil(count / 8.0);

    size_t buffer_len = 6 + bytes;
    char * buffer = (char *) malloc(sizeof(char) * buffer_len);

    bufc(buffer, FC_WRITE_MULTIPLE_COILS);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], count);
    buffer[5] = bytes;

    uint16_t index = 0;
    for(int i = 0; i < bytes; i++) {
        char c = 0x00;

        for(int j = 0; j < 8 && index < count; j++) {
            if (value[index++]) {
                c |= (1 << j);
            }
        }

        buffer[6 + i] = c;
    }

    write(buffer, buffer_len);
    free(buffer);

    read_response(FC_WRITE_MULTIPLE_COILS);

    uint8_t * coils = read_bits(&count);
    
    if(callback != NULL) {
        callback(coils, count);
    }

    free(coils);
}

void master_write_single_register(m_reg_address address, uint16_t value, read_word_callback callback) {
    char buffer[5];

    bufc(buffer, FC_WRITE_SINGLE_REGISTER);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], value);

    write(buffer, sizeof(buffer));

    read_response(FC_WRITE_SINGLE_REGISTER);

    uint16_t count = 1;
    uint16_t * words = read_words(&count);
    
    if(callback != NULL) {
        callback(words[0]);
    }

    free(words);
}

void master_write_multiple_registers(m_reg_address address, uint16_t * values, uint16_t count, read_words_callback callback) {
    uint16_t bytes = count * 2;

    size_t buffer_len = 6 + bytes;
    char * buffer = (char *) malloc(sizeof(char) * buffer_len);

    bufc(buffer, FC_WRITE_MULTIPLE_REGISTERS);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], count);
    buffer[5] = bytes;

    for(int i = 0; i < count; i++) {
        bufi16(&buffer[6 + i * 2], values[i]);
    }

    write(buffer, buffer_len);
    free(buffer);

    read_response(FC_WRITE_MULTIPLE_REGISTERS);

    uint16_t * words = read_words(&count);
    
    if(callback != NULL) {
        callback(words, count);
    }

    free(words);
}
