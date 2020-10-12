#ifndef FUNC_WRITE_H
#define FUNC_WRITE_H 1

#include "modbus/common/types.h"
#include "modbus/common/functions/functions.h"
#include "modbus/common/functions/codes.h"

#include "modbus/transport/transport.h"

void master_write_single_coil(m_reg_address address, uint8_t value, read_bit_callback callback);

void master_write_multiple_coils(m_reg_address address, uint8_t * values, uint16_t count, read_bits_callback callback);

void master_write_single_register(m_reg_address address, uint16_t value, read_word_callback callback);

void master_write_multiple_registers(m_reg_address address, uint16_t * values, uint16_t count, read_words_callback callback);

#endif