#include "my_nm.h"

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
        init_symb_list(gen, tmp);
    }
    for (file_t *tmp = gen->file; tmp; tmp = tmp->next)
        print_symb(gen, tmp);
    return (gen->ret);
}