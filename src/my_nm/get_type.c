#include "my_nm.h"

void get_type_next_nn(Elf64_Shdr *section, Elf64_Sym *symb, char *type, int i)
{
    if (section[symb[i].st_shndx].sh_type == SHT_PROGBITS && \
    section[symb[i].st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        (*type) = 'T';
    else
        (*type) = '?';
}

void get_type_next_n(Elf64_Shdr *section, Elf64_Sym *symb, char *type, int i)
{
    if ((section[symb[i].st_shndx].sh_type == SHT_PROGBITS && \
    section[symb[i].st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) || \
    section[symb[i].st_shndx].sh_type == SHT_DYNAMIC)
        (*type) = 'D';
    else if (section[symb[i].st_shndx].sh_type == SHT_PROGBITS && \
    section[symb[i].st_shndx].sh_flags == SHF_ALLOC)
        (*type) = 'R';
    else
        get_type_next_nn(section, symb, type, i);
    if (ELF64_ST_BIND(symb[i].st_info) == STB_WEAK)
        (*type) = (symb[i].st_shndx != SHN_UNDEF) ? 'W' : 'w';
    if ((*type) != '?' && ELF64_ST_BIND(symb[i].st_info) != STB_GLOBAL)
        (*type) += 32;
}

void get_type_next(Elf64_Shdr *section, Elf64_Sym *symb, char *type, int i)
{
    if (symb[i].st_shndx == SHN_COMMON)
        (*type) = 'C';
    else if (section[symb[i].st_shndx].sh_type == SHT_NOBITS && \
    section[symb[i].st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        (*type) = 'B';
    else
        get_type_next_n(section, symb, type, i);
}

char get_type(gen_t *gen, int i)
{
    char type = 0;
    Elf64_Sym *symb = gen->data->symb;
    Elf64_Shdr *section = gen->data->section;

    if (symb[i].st_shndx == SHN_UNDEF)
        type = 'U';
    else if (symb[i].st_shndx == SHN_ABS)
        type = 'A';
    else
        get_type_next(section, symb, &type, i);
    return (type);
}