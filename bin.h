#ifndef MOO1_PATCHER_BIN_H
#define MOO1_PATCHER_BIN_H

#include <stdint.h>
#include <stdio.h>

extern int bin_check(FILE *f, int offset, const uint8_t str[], int len);
extern int bin_check_nop(FILE *f, int offset, int len);
extern int bin_set_nop(FILE *f, int offset, int len);
extern int bin_replace(FILE *f, int offset, const uint8_t str[], int len);

#endif
