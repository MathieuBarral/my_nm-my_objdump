#include "my_nm.h"

void push_in_symb_list(symb_t **head, symb_t *new_node)
{
    symb_t *tmp = *head;

    if (!(*head))
        (*head) = new_node;
    else {
        for (; tmp->next; tmp = tmp->next);
        new_node->prev = tmp;
        tmp->next = new_node;
    }
}

symb_t *create_symb_node(gen_t *gen, int i)
{
    char type = get_type(gen, i);
    Elf64_Sym *symb = gen->data->symb;
    symb_t *new_node = malloc(sizeof(symb_t));
    char *symb_name = gen->data->symb_name + symb[i].st_name;

    new_node->symb_name = malloc(sizeof(char) * (strlen(symb_name) + 1));
    memset(new_node->symb_name, '\0', (strlen(symb_name) + 1));
    strcpy(new_node->symb_name, symb_name);
    new_node->type = type;
    new_node->value = (type != 'U' && type != 'w') ? symb[i].st_value : 0;
    new_node->prev = NULL;
    new_node->next = NULL;
    return (new_node);
}

void init_symb_list(gen_t *gen, file_t *file)
{
    Elf64_Sym *symb = gen->data->symb;
    char *symb_name = gen->data->symb_name;

    if (!(file->is_valid) || file->is_valid == 2)
        return;
    for (int i = 0; i < gen->data->symb_num; i++) {
        if (symb[i].st_name && \
        strstr(symb_name + symb[i].st_name, ".c") == NULL)
            push_in_symb_list(&(file->symb_str), create_symb_node(gen, i));
    }
}