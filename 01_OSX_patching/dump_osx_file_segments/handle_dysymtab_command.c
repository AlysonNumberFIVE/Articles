

#include "packer.h"

/*
struct dysymtab_command {
    uint32_t cmd;	// LC_DYSYMTAB 
    uint32_t cmdsize;	// sizeof(struct dysymtab_command) 
    uint32_t ilocalsym;	// index to local symbols 
    uint32_t nlocalsym;	// number of local symbols 

    uint32_t iextdefsym;// index to externally defined symbols 
    uint32_t nextdefsym;// number of externally defined symbols 

    uint32_t iundefsym;	// index to undefined symbols 
    uint32_t nundefsym;	// number of undefined symbols 

    uint32_t tocoff;	// file offset to table of contents 
    uint32_t ntoc;	// number of entries in table of contents 
    uint32_t modtaboff;	// file offset to module table 
    uint32_t nmodtab;	// number of module table entries 
    uint32_t extrefsymoff;	//i offset to referenced symbol table 
    uint32_t nextrefsyms;	// number of referenced symbol table entries 
    uint32_t indirectsymoff; // file offset to the indirect symbol table 
    uint32_t nindirectsyms;  // number of indirect symbol table entries
    uint32_t extreloff;	// offset to external relocation entries 
    uint32_t nextrel;	// number of external relocation entries 
    uint32_t locreloff;	// offset to local relocation entries 
    uint32_t nlocrel;	// number of local relocation entries 

};	*/

void handle_dysymtab_command(struct load_command *loader)
{
    struct dysymtab_command *dysymtab;
    extern size_t set_point;

    dysymtab = (struct dysymtab_command *)loader;
    /*
    printf("index to localsymbotl %u\n", dysymtab->ilocalsym);
    printf("index to iexdefsym %u\n", dysymtab->iextdefsym);
    printf("tocoff : %u\n", dysymtab->tocoff);
    printf("modtaboff : %u\n", dysymtab->modtaboff);
    printf("extrefsymoff : %u\n", dysymtab->extrefsymoff);
    printf("locreloff : %u\n", dysymtab->locreloff);
    */
}
