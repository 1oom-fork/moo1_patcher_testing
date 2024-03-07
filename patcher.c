#include <stdint.h>
#include <stdio.h>

int moobin_check(FILE *f, int offset, const uint8_t str[], int len)
{
    fseek(f, offset, SEEK_SET);
    for (int i = 0; i < len; ++i) {
        if (feof(f) || ferror(f)) {
            printf("feof/ferror\n");
            return -1;
        }
        uint8_t c = getc(f) & 0xff;
        if (c != str[i]) {
            printf("Wrong file\n");
            return -2;
        }
    }
    return 0;
}

int moobin_set_nop(FILE *f, int offset, int len)
{
    fseek(f, offset, SEEK_SET);
    for (int i = 0; i < len; ++i) {
        if (feof(f) || ferror(f)) {
            printf("feof/ferror\n");
            return -1;
        }
        putc(0x90, f);
    }
    return 0;
}

int moobin_replace(FILE *f, int offset, const uint8_t str[], int len)
{
    fseek(f, offset, SEEK_SET);
    for (int i = 0; i < len; ++i) {
        if (feof(f) || ferror(f)) {
            printf("feof/ferror\n");
            return -1;
        }
        putc(str[i], f);
    }
    return 0;
}

int fix_ship_scanners(FILE *f)
{
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
    if (moobin_check(f, 0x6d96e, match1, len1)) {
        if (!moobin_check(f, 0x6d99b, replace2, len2)) {
            printf("Already patched?\n");
        }
        return -1;
    }
    if (moobin_check(f, 0x6d99b, match2, len2)) {
        return -1;
    }
    // Check https://github.com/1oom-fork/1oom
    moobin_set_nop(f, 0x6d96e, len1);   // See 80eac9857a4d41492876120fdfe95e091f53d724
    moobin_replace(f, 0x6d99b, replace2, len2); // See 671042a99fa00a701e23d310b8f7acbe3c8b5d63
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
