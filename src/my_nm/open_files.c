#include "my_nm.h"

char *open_read_file(const char *filename)
{
    int fd = 0;
    struct stat s;
    char *buff = NULL;

    if ((fd = open(filename, O_RDONLY)) == -1)
        return (NULL);
    fstat(fd, &s);
    buff = malloc(sizeof(char) * (s.st_size + 1));
    memset(buff, '\0', (s.st_size + 1));
    read(fd, buff, s.st_size);
    return (buff);
}

void open_files(int argc, char **argv, gen_t *gen)
{
    for (int index = 1; index < argc; index++, gen->nb_file++)
        push_in_list(&(gen->file), create_node(argv[index]));
}