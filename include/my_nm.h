#ifndef MY_NM_H
    #define MY_NM_H

    #include <elf.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>

    // Symbole node structure
    typedef struct symb_s {
        char type;
        char *symb_name;
        u_int32_t value;
        struct symb_s *prev;
        struct symb_s *next;
    } symb_t;

    // File node structure
    typedef struct file_s {
        char *buff;
        int is_valid;
        char *filename;
        symb_t *symb_str;
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
     * @brief Print all symbols
     *
     * @param gen
     * @param file
     *
     * @return none
     */
    void print_symb(gen_t *gen, file_t *file);

    /**
     * @brief Get the type of an symbol
     *
     * @param gen
     * @param i
     *
     * @return char
     */
    char get_type(gen_t *gen, int i);

    /**
     * @brief Init symbol structure
     *
     * @param gen
     * @param file
     *
     * @return none
     */
    void init_symb_list(gen_t *gen, file_t *file);

#endif