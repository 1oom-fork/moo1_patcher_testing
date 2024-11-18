#include "bin.h"

int bin_check(FILE *f, int offset, const uint8_t str[], int len)
{
    fseek(f, offset, SEEK_SET);
    if (feof(f) || ferror(f)) {
        printf("feof/ferror\n");
        return -1;
    }
    for (int i = 0; i < len; ++i) {
        uint8_t c = getc(f) & 0xff;
        if (feof(f) || ferror(f)) {
            printf("feof/ferror\n");
            return -1;
        }
        if (c != str[i]) {
            return -2;
        }
    }
    return 0;
}

int bin_check_nop(FILE *f, int offset, int len)
{
    fseek(f, offset, SEEK_SET);
    if (feof(f) || ferror(f)) {
        printf("feof/ferror\n");
        return -1;
    }
    for (int i = 0; i < len; ++i) {
        uint8_t c = getc(f) & 0xff;
        if (feof(f) || ferror(f)) {
            printf("feof/ferror\n");
            return -1;
        }
        if (c != 0x90) {
            return -2;
        }
    }
    return 0;
}

int bin_set_nop(FILE *f, int offset, int len)
{
    fseek(f, offset, SEEK_SET);
    if (feof(f) || ferror(f)) {
        printf("feof/ferror\n");
        return -1;
    }
    for (int i = 0; i < len; ++i) {
        putc(0x90, f);
        if (feof(f) || ferror(f)) {
            printf("feof/ferror\n");
            return -1;
        }
    }
    return 0;
}

int bin_replace(FILE *f, int offset, const uint8_t str[], int len)
{
    fseek(f, offset, SEEK_SET);
    if (feof(f) || ferror(f)) {
        printf("feof/ferror\n");
        return -1;
    }
    for (int i = 0; i < len; ++i) {
        putc(str[i], f);
        if (feof(f) || ferror(f)) {
            printf("feof/ferror\n");
            return -1;
        }
    }
    return 0;
}
