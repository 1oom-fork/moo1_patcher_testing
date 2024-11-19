#ifndef MOO1_PATCHER_PATCH_H
#define MOO1_PATCHER_PATCH_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    const uint8_t *match;
    const uint8_t *replace;
    int offset;
    int len;
} patch_t;

typedef enum {
    PATCH_STATUS_INVALID = 0,
    PATCH_STATUS_ORIGINAL,
    PATCH_STATUS_PATCHED,
    PATCH_STATUS_NUM,
} patch_status_t;

extern patch_status_t get_patch_status(FILE *f, const patch_t *patch);
extern void apply_patch(FILE *f, const patch_t *patch);
extern void remove_patch(FILE *f, const patch_t *patch);

extern patch_status_t get_patch_set_status(FILE *f, const patch_t *patch_set);
extern void apply_patch_set(FILE *f, const patch_t *patch_set);
extern void remove_patch_set(FILE *f, const patch_t *patch_set);

#endif
