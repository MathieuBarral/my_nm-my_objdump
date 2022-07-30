#include "my_objdump.h"

void print_header(gen_t *gen, file_t *file)
{
    Elf64_Ehdr *head = gen->data->head;
    int flags = 0;

    if (!(file->is_valid)) {
        fprintf(stderr, "my_objdump: %s: file format not recognized\n", \
        file->filename);
        gen->ret = 84;
        return;
    } else if (file->is_valid == 2) {
        fprintf(stderr, "my_objdump: '%s': No such file\n", file->filename);
        gen->ret = 84;
        return;
    }
    flags = get_flags(gen);
    printf("\n%s:     file format elf64-x86-64\n", file->filename);
    printf("architecture: i386:x86-64, flags 0x%0*x:\n", (unsigned int) 8, \
    flags);
    print_flags(flags);
    printf("start address 0x%0*x\n\n", (unsigned int) 16, \
    (unsigned int) head->e_entry);
}

void print_section_name(gen_t *gen, file_t *file)
{
    Elf64_Ehdr *head = gen->data->head;
    Elf64_Shdr *section = gen->data->section;
    Elf64_Shdr *sh_strtab = NULL;
    char *str = NULL;

    if (file->is_valid == 2)
        return;
    sh_strtab = &section[head->e_shstrndx];
    str = (char *) head + sh_strtab->sh_offset;
    for (int index = 0; index < head->e_shnum; index++) {
        if (section[index].sh_name && \
        !strstr(str + section[index].sh_name, "tab") && \
        strcmp(str + section[index].sh_name, ".bss"))
            printf("Contents of section %s:\n", str + section[index].sh_name);
    }
}

int main(int argc, char **argv)
{
    gen_t *gen = malloc(sizeof(gen_t));
    gen->data = malloc(sizeof(data_t));
    gen->nb_file = 0;
    gen->file = NULL;
    gen->ret = 0;

    if (argc <= 1)
        return (84);
    open_files(argc, argv, gen);
    for (file_t *tmp = gen->file; tmp; tmp = tmp->next) {
        init_data(gen, tmp);
        print_header(gen, tmp);
        print_section_name(gen, tmp);
    }
    return (gen->ret);
}