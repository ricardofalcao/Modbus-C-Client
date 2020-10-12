#ifndef FUNC_READ_H
#define FUNC_READ_H 1

#include "modbus/common/types.h"
#include "modbus/common/functions/functions.h"
#include "modbus/common/functions/codes.h"

#include "modbus/transport/transport.h"

void master_read_coils(m_reg_address address, uint16_t count, read_bits_callback callback);

void master_read_discrete_inputs(m_reg_address address, uint16_t count, read_bits_callback callback);

void master_read_holding_registers(m_reg_address address, uint16_t count, read_words_callback callback);

void master_read_input_registers(m_reg_address address, uint16_t count, read_words_callback callback);

#endif