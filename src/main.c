#include <stdio.h>

#include "modbus/transport/transport.h"
#include "modbus/master/functions/read/read.h"
#include "modbus/master/functions/write/write.h"

void coil_callback(const uint8_t * data, const size_t len) {
    for(uint8_t i  =0; i < len; i++) {
        printf("Bit %d: %d\n", i, data[i]);
    }
}

void word_callback(const uint16_t * data, const size_t len) {
    for(uint8_t i  =0; i < len; i++) {
        printf("Word %d: %d\n", i, data[i]);
    }
}

int main() {
    m_reg_address addr = 0x00;

    uint8_t data[] = { 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0 }; 
    master_write_multiple_coils(addr, data, 14, NULL);
    master_read_coils(addr, 14, &coil_callback);

    addr = 0x1A;

    uint16_t data2[] = { 1, 2, 3, 1, 2, 3, 0, 0, 4, 5, 1, 10, 1, 0 }; 
    master_write_multiple_registers(addr, data2, 14, NULL);
    master_read_holding_registers(addr, 14, &word_callback);
    return 0;
}