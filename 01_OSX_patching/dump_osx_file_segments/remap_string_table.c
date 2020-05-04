

#include "packer.h"
#include <mach-o/nlist.h>

void  print_string_table_section(unsigned char *file_content, 
    int start_index, int number_of_symbols)
{
    int string_counter;
    int sym_counter;

    string_counter = start_index;
    sym_counter = 0;
   // printf("number of symbols : %u\n", number_of_symbols);
   // printf("start of string table at index %u=========================\n", start_index);
    while (sym_counter < number_of_symbols + 1)
    {
        if (file_content[string_counter]== '\0')
        {
            sym_counter++;
        //    printf("\n");
        }
       // else
       //     printf("%c", file_content[string_counter]);
        string_counter++;
    }
   // printf("end ofsection : %lu===========================\n", string_counter);
}


void    print_symbol_table(unsigned char *file_content,
    struct nlist_64 *start, int start_index, int number_of_syms)
{
    int                 counter;
    struct nlist_64     *listing;
    int                 ending_index;

    counter = 0;
    ending_index = start_index;
   // printf("starting index of Symbol Table : %u===================\n", start_index);
    while (counter < number_of_syms + 1)
    {
        listing = &start[counter];
        ending_index += sizeof(struct nlist_64);
     //   printf("%d\n", sizeof(struct nlist_64));
        counter++;
    }
   // printf("neding of Symbol Table ; %u============================\n", ending_index);

}


void   save_current_string_tabe(struct load_command *loader,
    unsigned char *file_content)
{
    struct symtab_command   *symtab;
    const char               *string_table;
    int                      counter;
    struct nlist_64         *symbol_table;
    struct nlist_64         *traveler;
    const char              *string_name;

    symtab = (struct symtab_command *)loader;
    string_table = (const char *)(file_content + symtab->stroff);
//    printf("string table offset : %u\n", symtab->stroff);
    symbol_table = (struct nlist_64 *)((void *)file_content + symtab->symoff);
//    printf("Symbol table offset : %lu\n", symtab->symoff);
    counter = 0;
    while (counter < symtab->nsyms)
    {
        traveler = (struct nlist_64 *)symbol_table;
//        printf("symbol table size : %lu\n", sizeof(struct nlist_64));
         
        string_name = &string_table[traveler->n_un.n_strx];
       //  printf("%s\n", string_name);
        symbol_table = (struct nlist_64 *)((void *)symbol_table + sizeof(struct nlist_64));
        counter++;
    }
    print_string_table_section(file_content, symtab->stroff, symtab->nsyms);
    print_symbol_table(file_content, symbol_table, symtab->symoff, symtab->nsyms); 
}







