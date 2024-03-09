#include <stdint.h>
#include <stdio.h>

int moobin_check(FILE *f, int offset, const uint8_t str[], int len)
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

int moobin_check_nop(FILE *f, int offset, int len)
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

int moobin_set_nop(FILE *f, int offset, int len)
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

int moobin_replace(FILE *f, int offset, const uint8_t str[], int len)
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

int fix_ship_scanners(FILE *f)
{
    const uint8_t match0[] = {
        0x83, 0x7e, 0xe6, 0x00, 0x7f, 0x03, 0xe9, 0xd8, 0x00
    };
    int len0 = 9;
    const uint8_t match1[] = {
        0x8b, 0x46, 0xec, 0xbb, 0x0a, 0x00, 0x99, 0xf7, 0xfb, 0x0b,
        0xd2, 0x75, 0x0b, 0x8b, 0x46, 0xec, 0xbb, 0x0a, 0x00, 0x99,
        0xf7, 0xfb, 0xeb, 0x0a, 0x8b, 0x46, 0xec, 0xbb, 0x0a, 0x00,
        0x99, 0xf7, 0xfb, 0x40, 0x89, 0x46, 0xec
    };
    int len1 = 37;
    const uint8_t match2[] = {
        0x8b, 0x46, 0xf2, 0x89, 0x46, 0xec
    };
    const uint8_t replace2[]={
        0x8b, 0x46, 0xec, 0x89, 0x46, 0xf2
    };
    int len2 = 6;
    if (moobin_check(f, 0x6d8f5, match0, len0)) {
        if (moobin_check_nop(f, 0x6d8f5, len0)) {
            printf("Wrong file\n");
            return -1;
        } else {
            printf("Warning: Chunk 0 has already been applied\n");
        }
    }
    if (moobin_check(f, 0x6d96e, match1, len1)) {
        if (moobin_check_nop(f, 0x6d96e, len1)) {
            printf("Wrong file\n");
            return -1;
        } else {
            printf("Warning: Chunk 1 has already been applied\n");
        }
    }
    if (moobin_check(f, 0x6d99b, match2, len2)) {
        if (moobin_check(f, 0x6d99b, replace2, len2)) {
            printf("Wrong file\n");
            return -1;
        } else {
            printf("Warning: Chunk 2 has already been applied\n");
        }
    }
    // Check https://github.com/1oom-fork/1oom
    moobin_set_nop(f, 0x6d8f5, len0);   // See 9eee0ac925e4c721f6ebc27d1dfa14307b16c098
    moobin_set_nop(f, 0x6d96e, len1);   // See af4ba8540867d4afb63c5227c7b581e8260f845c
    moobin_replace(f, 0x6d99b, replace2, len2); // See f494885b9a7b2f28546abc0ee2921e379bb342b9
    return 0;
}

int main(int argc, char **argv)
{
    FILE *f = fopen("STARMAP.EXE", "r+b");
    if (!f) {
        printf("STARMAP.EXE not found\n");
        return -1;
    }
    if (fix_ship_scanners(f)) {
        printf("Fail\n");
    }
    if (f) {
        fclose(f);
    }
    return 0;
}
