#ifndef FUNC_H
#define FUNC_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "buffer/buffer.h"

#include "modbus/common/types.h"
#include "modbus/common/functions/functions.h"
#include "modbus/common/functions/codes.h"

#include "modbus/transport/transport.h"

size_t read_response(char _code);

uint8_t * read_bits(uint16_t * count);

uint16_t * read_words(uint16_t * count);

#endif