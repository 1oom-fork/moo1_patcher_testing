#include <stdint.h>
#include <stdio.h>

#include "patcher.h"

int main(int argc, char **argv)
{
    const uint8_t match0[] = {
        0x83, 0x7e, 0xe6, 0x00, 0x7f, 0x03, 0xe9, 0xd8, 0x00
    };
    int len0 = 9;
    int off0 = 0x6d8f5;
    const uint8_t match1[] = {
        0x8b, 0x46, 0xec, 0xbb, 0x0a, 0x00, 0x99, 0xf7, 0xfb, 0x0b,
        0xd2, 0x75, 0x0b, 0x8b, 0x46, 0xec, 0xbb, 0x0a, 0x00, 0x99,
        0xf7, 0xfb, 0xeb, 0x0a, 0x8b, 0x46, 0xec, 0xbb, 0x0a, 0x00,
        0x99, 0xf7, 0xfb, 0x40, 0x89, 0x46, 0xec
    };
    int len1 = 37;
    int off1 = 0x6d96e;
    const uint8_t match2[] = {
        0x8b, 0x46, 0xf2, 0x89, 0x46, 0xec
    };
    const uint8_t replace2[]={
        0x8b, 0x46, 0xec, 0x89, 0x46, 0xf2
    };
    int len2 = 6;
    int off2 = 0x6d99b;
    const patch_t patch_set[] = {          // Check https://github.com/1oom-fork/1oom
        {match0, NULL, off0, len0},         // See 9eee0ac925e4c721f6ebc27d1dfa14307b16c098
        {match1, NULL, off1, len1},         // See af4ba8540867d4afb63c5227c7b581e8260f845c
        {match2, replace2, off2, len2},     // See f494885b9a7b2f28546abc0ee2921e379bb342b9
        {NULL, NULL, 0, 0},
    };
    patch_status_t result = execute_patcher("STARMAP.EXE", patch_set);
    if (result == PATCH_STATUS_INVALID) {
        printf("Fail\n");
    }
    getchar();
    return 0;
}
