#include <stdint.h>
#include <stdio.h>

#include "patcher.h"

int main(int argc, char **argv)
{
    const uint8_t match0[] = {
        0x9A, 0x25, 0x00, 0x45, 0x32, 0xC7, 0x06, 0x20, 0x77, 0x01,
        0x00,
    };
    int len0 = 11;
    int off0 = 0xcc98;
    const patch_t patch_set[] = {
        {match0, NULL, off0, len0},
        {NULL, NULL, 0, 0},
    };
    patch_status_t result = execute_patcher("STARMAP.EXE", patch_set);
    if (result == PATCH_STATUS_INVALID) {
        printf("Fail\n");
    }
    getchar();
    return 0;
}
