#include "my_nm.h"

void init_struct(data_t **data, file_t *file)
{
    for (int index = 0; index < (*data)->head->e_shnum; index++) {
        if ((*data)->section[index].sh_type == SHT_SYMTAB) {
            (*data)->symb_num = ((*data)->section[index].sh_size / \
            (*data)->section[index].sh_entsize);
            (*data)->symb = (Elf64_Sym *) (file->buff + \
            (*data)->section[index].sh_offset);
            (*data)->symb_name = (char *) (file->buff + \
            (*data)->section[(*data)->section[index].sh_link].sh_offset);
        }
    }
}

void init_data(gen_t *gen, file_t *file)
{
    data_t **data = &gen->data;
    char magic[] = {0x7f, 0x45, 0x4c, 0x46, 0x02, 0x01, 0x01};

    if (file->is_valid == 2)
        return;
    (*data)->head = (Elf64_Ehdr *) file->buff;
    if (strncmp((const char *) gen->data->head->e_ident, magic, 7) == 0)
        file->is_valid = 1;
    else
        return;
    (*data)->section = (Elf64_Shdr *) (file->buff + (*data)->head->e_shoff);
    init_struct(data, file);
}