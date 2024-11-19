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
