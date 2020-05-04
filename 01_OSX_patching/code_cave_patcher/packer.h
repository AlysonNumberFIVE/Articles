


#ifndef PACKER_H
#define PACKER_H

#define X 16
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <string.h>

typedef struct s_file_segments
{
    size_t  start_index;
    size_t  end_index;
    char    *area_name;
    void    *section_contents;
    struct s_file_segments *next;
}   t_format;


t_format  *push_segment(t_format *segment_head, size_t start_inde, size_t end_index, unsigned char *content, char *area_name);
void    print_load_command_names(int load_name);
void    handle_dyld_info_comamnd(struct load_command *dyld_block, unsigned char *content);
void    handle_symtab_command(struct load_command *symtab_section);
void    handle_linkedit_data_command(struct load_command *loader, unsigned char *content);
void    handle_segment_64(struct load_command *loader, unsigned char*file_content);
void    handle_dysymtab_command(struct load_command *loader);
void   save_current_string_tabe(struct load_command *loader,
    unsigned char *file_content);
int     seg_length(t_format *seg);
void    merge_sort(t_format **segment);
#endif
