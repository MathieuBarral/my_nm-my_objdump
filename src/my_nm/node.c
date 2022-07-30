#include "my_nm.h"

file_t *create_node(const char *filename)
{
    char *tmp = open_read_file(filename);
    file_t *new_node = malloc(sizeof(file_t));

    new_node->filename = malloc(sizeof(char) * (strlen(filename) + 1));
    memset(new_node->filename, '\0', (strlen(filename) + 1));
    strcpy(new_node->filename, filename);
    new_node->is_valid = (tmp) ? 0 : 2;
    new_node->buff = tmp;
    new_node->next = NULL;
    return (new_node);
}

void push_in_list(file_t **head, file_t *new_node)
{
    file_t *tmp = *head;

    if (!(*head))
        (*head) = new_node;
    else {
        for (; tmp->next; tmp = tmp->next);
        tmp->next = new_node;
    }
}