#include <stdint.h>
#include <stdio.h>

#include "patcher.h"

int main(int argc, char **argv)
{
    const uint8_t match0[] = {
        0x8B, 0xC6, 0xBA, 0x26, 0x00, 0xF7, 0xEA, 0xC4, 0x1E, 0x6E,
        0xEC, 0x03, 0xD8, 0x26, 0x81, 0x3F, 0x40, 0x01, 0x7C, 0x03
    };
    int len0 = 20;
    int off0 = 0x2a84c;
    const uint8_t match1[] = {
        0xFF, 0x76, 0x0A, 0x57, 0x9A, 0x78, 0x06, 0x3E, 0x25, 0x59,
        0x59
    };
    int len1 = 11;
    int off1[] = {
        0x312f8, 0x313de, 0x3142a
    };
    int num1 = 3;
    const uint8_t match2[] = {
        0x8B, 0xC6, 0xBA, 0x26, 0x00, 0xF7, 0xEA, 0xC4, 0x1E, 0x6E,
        0xEC, 0x03, 0xD8, 0x26, 0x83, 0x7F, 0x08, 0x04, 0x75, 0x0F
    };
    int len2 = 20;
    int off2[] = {
        0x312bf, 0x313a5
    };
    int num2 = 2;
    const uint8_t match3[] = {
        0xFF, 0x76, 0xFA, 0x9A, 0x9C, 0x1F, 0x15, 0x26, 0x59
    };
    int len3 = 9;
    int off3 = 0x15ea5;
    const patch_t patch_set[] = {
        {match0, NULL, off0, len0},
        {match1, NULL, off1[0], len1},
        {match1, NULL, off1[1], len1},
        //{match1, NULL, off1[2], len1},
        {match2, NULL, off2[0], len2},
        {match2, NULL, off2[1], len2},
        {match3, NULL, off3, len3},
        {NULL, NULL, 0, 0},
    };
    // Check https://github.com/1oom-fork/1oom
    // See 26a29666fd87a59f1a8765ca34ef0a4c712004e8 and 28def32346d5b3704a510567f7809f7cfc48b442
    patch_status_t result = execute_patcher("STARMAP.EXE", patch_set);
    if (result == PATCH_STATUS_INVALID) {
        printf("Fail\n");
    }
    getchar();
    return 0;
}
