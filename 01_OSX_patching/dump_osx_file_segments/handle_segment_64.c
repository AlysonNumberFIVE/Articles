
#include "packer.h"
/*
struct segment_command_64 { // for 64-bit architectures 
	uint32_t	cmd;		// LC_SEGMENT_64 
	uint32_t	cmdsize;	// includes sizeof section_64 structs 
	char		segname[16];	// segment name 
	uint64_t	vmaddr;		// memory address of this segment 
	uint64_t	vmsize;		// memory size of this segment 
	uint64_t	fileoff;	// file offset of this segment 
	uint64_t	filesize;	// amount to map from the file
	vm_prot_t	maxprot;	// maximum VM protection 
	vm_prot_t	initprot;	// initial VM protection 
	uint32_t	nsects;		// number of sections in segment 
	uint32_t	flags;		// flags flags 
};

struct section_64 { // for 64-bit architectures 
	char		sectname[16];	// name of this section 
	char		segname[16];	// segment this section goes in 
	uint64_t	addr;		// memory address of this section 
	uint64_t	size;		// size in bytes of this section 
	uint32_t	offset;		// file offset of this section 
	uint32_t	align;		// section alignment (power of 2) 
	uint32_t	reloff;		// file offset of relocation entries 
	uint32_t	nreloc;		// number of relocation entries 
	uint32_t	flags;		// flags (section type and attriutes)
	uint32_t	reserved1;	// reserved (for offset or index) 
	uint32_t	reserved2;	// reserved (for count or sizeof)
	uint32_t	reserved3;	// reserved 
};
*/


static void handle_section_64(struct segment_command_64 *segment64,
        unsigned char *content)
{
    struct section_64 *section64;
    int counter;
    extern t_format *segment;

    section64 = (struct section_64 *)&segment64[1];
    counter = 0;
    while (counter < segment64->nsects)
    {
        if (section64->size > 0)
            segment =  push_segment(segment, section64->offset,
                section64->offset + section64->size,
                content,
                section64->sectname);
        section64 = (struct section_64 *)((void*)section64 +sizeof(struct section_64));;
        counter++;
    }
} 

void handle_segment_64(struct load_command *loader, unsigned char *content)
{
    struct segment_command_64 *segment64;
    extern size_t file_offset;
    extern t_format *segment;

    segment64 = (struct segment_command_64 *)loader;
//    file_offset += segment64->vmsize;

    file_offset += segment64->filesize;

    /*
    segment = push_segment(segment, segment64->fileoff,
        segment64->fileoff + segment64->filesize,
        content, "LC_SEGMENT_64");*/
    handle_section_64(segment64, content);
}





