#ifndef TYPES_H
#define TYPES_H 1

#include <stdint.h>
#include <stddef.h>

typedef uint16_t m_reg_address;

typedef void (*read_bits_callback)(const uint8_t *, const size_t len);
typedef void (*read_bit_callback)(const uint8_t);
typedef void (*read_words_callback)(const uint16_t *, const size_t len);
typedef void (*read_word_callback)(const uint16_t);

#endif