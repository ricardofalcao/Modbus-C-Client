#include "utils/utils.h"

void print_char_array(char * name, char * array, size_t len) {
    printf("%s", name);

    for (int i = 0; i < len; i++) {
        printf("%02x ", array[i] & 0xFF);
    }

    printf("\n");
}