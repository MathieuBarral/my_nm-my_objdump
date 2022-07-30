#ifndef MY_OBJDUMP_H
    #define MY_OBJDUMP_H

    #include <elf.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>

    #include "flags.h"

    // File node structure
    typedef struct file_s {
        char *buff;
        int is_valid;
        char *filename;
        struct file_s *next;
    } file_t;

    // Data node structure
    typedef struct data_s {
        int symb_num;
        char *symb_name;
        Elf64_Ehdr *head;
        Elf64_Shdr *section;
        Elf64_Sym *symb;
    } data_t;

    // General purpose structure
    typedef struct gen_s {
        int nb_file;
        int ret;
        file_t *file;
        data_t *data;
    } gen_t;


    /**
     * @brief Open files specified in stdin and add them in list
     *
     * @param argc
     * @param argv
     * @param gen
     *
     * @return none
     */
    void open_files(int argc, char **argv, gen_t *gen);

    /**
     * @brief Create a node and add in list
     *
     * @param filename
     *
     * @return file_t *
     */
    file_t *create_node(const char *filename);

    /**
     * @brief Open and read specified files
     *
     * @param filename
     *
     * @return char *
     */
    char *open_read_file(const char *filename);

    /**
     * @brief Push specified node in list
     *
     * @param head
     * @param new_node
     *
     * @return none
     */
    void push_in_list(file_t **head, file_t *new_node);

    /**
     * @brief Init data structure
     *
     * @param gen
     * @param file
     *
     * @return none
     */
    void init_data(gen_t *gen, file_t *file);

    /**
     * @brief Get flags of the file
     *
     * @param gen
     *
     * @return int
     */
    int get_flags(gen_t *gen);

    /**
     * @brief Print all flags
     *
     * @param flags
     *
     * @return none
     */
    void print_flags(int flags);

#endif