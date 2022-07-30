#include "my_objdump.h"

void check_symb(gen_t *gen, int *flags)
{
    Elf64_Ehdr *head = gen->data->head;
    Elf64_Shdr *section = gen->data->section;

    for (int index = 0; index < head->e_shnum; index++) {
        if (section != NULL)
        (*flags) += (section[index].sh_type == SHT_SYMTAB) ? HAS_SYMS : 0;
    }
}

void get_flags_next(Elf64_Ehdr *head, int *flags)
{
    (*flags) += (head->e_type == ET_REL) ? HAS_RELOC : 0;
}

int get_flags(gen_t *gen)
{
    int flags = 0;
    Elf64_Ehdr *head = gen->data->head;

    if (head->e_type == ET_EXEC)
        flags += EXEC_P + D_PAGED;
    else if (head->e_type == ET_DYN)
        flags += DYNAMIC + D_PAGED;
    else
        get_flags_next(head, &flags);
    check_symb(gen, &flags);
    return (flags);
}