#include "my_nm.h"

void print_symb(gen_t *gen, file_t *file)
{
    if (!(file->is_valid)) {
        fprintf(stderr, "my_nm: %s: file format not recognized\n", \
        file->filename);
        gen->ret = 84;
        return;
    } else if (file->is_valid == 2) {
        fprintf(stderr, "my_nm: '%s': No such file\n", file->filename);
        gen->ret = 84;
        return;
    }
    if (gen->nb_file > 1)
        printf("\n%s:\n", file->filename);
    for (symb_t *tmp = file->symb_str; tmp; tmp = tmp->next) {
        if (tmp->value)
            printf("%0*x ", (unsigned int) 16, tmp->value);
        else
            printf("%*s ", (unsigned int) 16, "");
        printf("%c %s\n", tmp->type, tmp->symb_name);
    }
}