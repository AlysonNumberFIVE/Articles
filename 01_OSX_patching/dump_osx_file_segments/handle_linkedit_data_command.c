



#include "packer.h"

/*
struct linkedit_data_command {
    uint32_t	cmd;		// LC_CODE_SIGNATURE, LC_SEGMENT_SPLIT_INFO,
                            //       or LC_FUNCTION_STARTS 
    uint32_t	cmdsize;	// sizeof(struct linkedit_data_command) 
    uint32_t	dataoff;	// file offset of data in __LINKEDIT segment
    uint32_t	datasize;	// file size of data in __LINKEDIT segment
};
*/

void    handle_linkedit_data_command(struct load_command *loader, unsigned char *content)
{
    struct linkedit_data_command *linkedit;
    extern size_t file_offset;
    extern size_t set_point;
    extern t_format *segment;

    linkedit = (struct linkedit_data_command *)loader;
    
    if (linkedit->datasize > 0)
        segment = push_segment(segment, linkedit->dataoff,
            linkedit->dataoff + linkedit->datasize,
            content, "_x_linkedit___LINKKEDIT_info");

    file_offset += linkedit->datasize;
}

