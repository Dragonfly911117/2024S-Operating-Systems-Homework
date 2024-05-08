#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <virtual_address>\n", argv[0]);
        return 1;
    }

    unsigned int virtual_addr = strtol(argv[1], NULL, 10);
    unsigned int page_mask = 0xFFFFF000;
    unsigned int offset_mask = 0x00000FFF;

    unsigned int page_num = (virtual_addr & page_mask) >> 12;
    unsigned int offset = virtual_addr & offset_mask;

    printf("The address %u contains:\n", virtual_addr);
    printf("page number=%u\n", page_num);
    printf("offset=%u\n", offset);

    return 0;
}
