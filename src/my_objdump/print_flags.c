#include "my_objdump.h"

char *get_flag_str(int flags)
{
    if (flags == HAS_RELOC)
        return ("HAS_RELOC");
    if (flags == EXEC_P)
        return ("EXEC_P");
    if (flags == HAS_DEBUG)
        return ("HAS_DEBUG");
    if (flags == HAS_SYMS)
        return ("HAS_SYMS");
    if (flags == HAS_LOCALS)
        return ("HAS_LOCALS");
    if (flags == DYNAMIC)
        return ("DYNAMIC");
    if (flags == D_PAGED)
        return ("D_PAGED");
    if (flags == 0)
        return ("NO_FLAGS");
    return ("NULL");
}

void print_flags(int flags)
{
    int index = 0;
    uint16_t flag_type[8] = {0, HAS_RELOC, EXEC_P, HAS_DEBUG, HAS_SYMS, \
    HAS_LOCALS, DYNAMIC, D_PAGED};

    for (; index < 7; index++) {
        if (flags & flag_type[index]) {
            printf("%s, ", get_flag_str(flag_type[index]));
            flags -= flag_type[index];
        }
    }
    if (flags & flag_type[index])
        printf("%s\n", get_flag_str(flag_type[index]));
}