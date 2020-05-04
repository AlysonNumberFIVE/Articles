


#include "packer.h"


/*
struct dyld_info_command {
   uint32_t   cmd;		// LC_DYLD_INFO or LC_DYLD_INFO_ONLY
   uint32_t   cmdsize;		// sizeof(struct dyld_info_command)
    uint32_t   rebase_off;	// file offset to rebase info 
    uint32_t   rebase_size;	// size of rebase info   
    uint32_t   bind_off;	// file offset to binding info   
    uint32_t   bind_size;	// size of binding info  
    uint32_t   weak_bind_off;	// file offset to weak binding info   
    uint32_t   weak_bind_size;  // size of weak binding info  
    uint32_t   lazy_bind_off;	// file offset to lazy binding info
    uint32_t   lazy_bind_size;  // size of lazy binding infs 
    uint32_t   export_off;	// file offset to lazy binding info 
    uint32_t   export_size;	// size of lazy binding infs 
};
*/

void    handle_dyld_info_comamnd(struct load_command *dyld_block,
        unsigned char *content)
{
    extern size_t file_offset;
    struct dyld_info_command *dyld;
    extern size_t set_point;
    extern t_format *segment;

    // Get all the file offsets for every part of the file.
    dyld = (struct dyld_info_command *)dyld_block;
    file_offset += dyld->rebase_size;

    if (dyld->rebase_size > 0)
    segment = push_segment(segment, dyld->rebase_off,
        dyld->rebase_off + dyld->rebase_size,
        content, "_x_rebase_info");


    if (dyld->bind_size > 0)
    segment = push_segment(segment, dyld->bind_off,
        dyld->bind_off + dyld->bind_size,
        content, "_x_bind_inof");


    if (dyld->weak_bind_size > 0)
    segment = push_segment(segment, dyld->weak_bind_off,
        dyld->weak_bind_off + dyld->weak_bind_size,
        content, "_x_waeb_bind_info");


    if (dyld->weak_bind_size > 0)
    segment = push_segment(segment, dyld->lazy_bind_off,
        dyld->lazy_bind_off + dyld->lazy_bind_size,
        content, "_x_weak_bind_info");


    if (dyld->export_size > 0)
    segment = push_segment(segment, dyld->export_off,
        dyld->export_off + dyld->export_size,
        content, "_x_export_info");

 }










