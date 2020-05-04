
#include "packer.h"


/*
struct symtab_command {
	uint32_t	cmd;		// LC_SYMTAB 
	uint32_t	cmdsize;	// sizeof(struct symtab_command) 
	uint32_t	symoff;		// symbol table offset 
	uint32_t	nsyms;		// number of symbol table entries 
	uint32_t	stroff;		// string table offset 
	uint32_t	strsize;	// string table size in bytes 
};*/

void    handle_symtab_command(struct load_command *symtab_section)
{
    struct symtab_command   *symtab;
    extern size_t file_offset;
    extern size_t set_point;

    // add the sizes of all the files together.
    symtab = (struct symtab_command *)symtab_section;
    
    if (symtab->symoff > set_point && set_point > 0)
    {
        symtab->symoff += X;
    }
    
    if (symtab->stroff > set_point && set_point > 0)
    {
        symtab->stroff += X;
    }
    file_offset += symtab->strsize;

}
