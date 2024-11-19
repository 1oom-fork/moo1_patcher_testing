#include "patch.h"
#include "bin.h"

patch_status_t get_patch_status(FILE *f, const patch_t *patch)
{
    if (!bin_check(f, patch->offset, patch->match, patch->len)) {
        return PATCH_STATUS_ORIGINAL;
    }
    else if (patch->replace) {
        if (!bin_check(f, patch->offset, patch->replace, patch->len)) {
            return PATCH_STATUS_PATCHED;
        }
    } else {
        if (!bin_check_nop(f, patch->offset, patch->len)) {
            return PATCH_STATUS_PATCHED;
        }
    }
    return PATCH_STATUS_INVALID;
}

void apply_patch(FILE *f, const patch_t *patch)
{
    if (patch->replace) {
        bin_replace(f, patch->offset, patch->replace, patch->len);
    } else {
        bin_set_nop(f, patch->offset, patch->len);
    }
}

void remove_patch(FILE *f, const patch_t *patch)
{
    bin_replace(f, patch->offset, patch->match, patch->len);
}

patch_status_t get_patch_set_status(FILE *f, const patch_t *patch_set)
{
    patch_status_t result = PATCH_STATUS_INVALID;
    for (int ci = 0; patch_set[ci].match != NULL; ++ci) {
        const patch_t *patch = &patch_set[ci];
        const patch_status_t status = get_patch_status(f, patch);
        if (status == PATCH_STATUS_INVALID) {
            return PATCH_STATUS_INVALID;
        }
        if (result == PATCH_STATUS_INVALID) {
            result = status;
        } else if (result != status) {
            return PATCH_STATUS_INVALID;
        }
    }
    return result;
}

void apply_patch_set(FILE *f, const patch_t *patch_set)
{
    for (int ci = 0; patch_set[ci].match != NULL; ++ci) {
        apply_patch(f, &patch_set[ci]);
    }
}

void remove_patch_set(FILE *f, const patch_t *patch_set)
{
    for (int ci = 0; patch_set[ci].match != NULL; ++ci) {
        remove_patch(f, &patch_set[ci]);
    }
}
