#include "read.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "buffer/buffer.h"

/*

*/

void master_read_coils(m_reg_address address, uint16_t count, read_bits_callback callback) {
    char buffer[5];

    bufc(buffer, FC_READ_COILS);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], count);

    write(buffer, sizeof(buffer));

    read_response(FC_READ_COILS);
    uint8_t * coils = read_bits(&count);
    callback(coils, count);
    free(coils);
}

void master_read_discrete_inputs(m_reg_address address, uint16_t count, read_bits_callback callback) {
    char buffer[5];

    bufc(buffer, FC_READ_DISCRETE_INPUTS);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], count);

    write(buffer, sizeof(buffer));

    read_response(FC_READ_DISCRETE_INPUTS);
    uint8_t * coils = read_bits(&count);
    callback(coils, count);
    free(coils);
}


void master_read_holding_registers(m_reg_address address, uint16_t count, read_words_callback callback) {
    char buffer[5];

    bufc(buffer, FC_READ_HOLDING_REGISTERS);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], count);

    write(buffer, sizeof(buffer));

    read_response(FC_READ_HOLDING_REGISTERS);
    uint16_t * words = read_words(&count);
    callback(words, count);
    free(words);
}


void master_read_input_registers(m_reg_address address, uint16_t count, read_words_callback callback) {
    char buffer[5];

    bufc(buffer, FC_READ_INPUT_REGISTERS);
    bufi16(&buffer[1], address);
    bufi16(&buffer[3], count);

    write(buffer, sizeof(buffer));

    read_response(FC_READ_INPUT_REGISTERS);
    uint16_t * words = read_words(&count);
    callback(words, count);
    free(words);
}