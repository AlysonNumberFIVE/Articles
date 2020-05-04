



#include "packer.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <sys/stat.h>


typedef struct s_codecaves 
{
    size_t  start_index;
    size_t  content_size;
    struct s_codecaves *next;
}   t_cave;

t_cave  *first_cave(size_t start_index, size_t content_size)
{
    t_cave  *new;

    new = (t_cave *)malloc(sizeof(t_cave));
    new->start_index = start_index;
    new->content_size = content_size;
    new->next = NULL;
    return (new);
}

t_cave  *add_cave(t_cave *first_cave, size_t start_index, size_t content_size)
{
    t_cave  *add;

    add = first_cave;
    while (add->next)
        add = add->next;
    add->next = (t_cave *)malloc(sizeof(t_cave));
    add->next->start_index = start_index;
    add->next->content_size = content_size;
    add->next->next = NULL;
    return (add);
}

t_cave  *push_cave(t_cave *cave, size_t start_index, size_t content_size)
{
    t_cave  *add;

    add = cave;
    if (add == NULL)
    {
        add = first_cave(start_index, content_size);
        cave = add;
    }
    else
    {
        add = add_cave(cave, start_index, content_size);
        add = cave;
    }
    return (add);
}


void	map_file(char *filename, unsigned char **content, size_t *size)
{
	struct stat	info;
	int		fd;

	fd = open(filename, O_RDONLY);
	fstat(fd, &info);
	*size = info.st_size;
	*content = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (*content == MAP_FAILED)
	{
		printf("Error mapping file\nExiting\n");
		exit(1);
	}
}

t_cave    *code_caves(unsigned char *content, size_t size)
{
    size_t counter;
    int flag;
    t_cave  *cave;

    int x = 0;
    flag = 1;
    counter = 0;
    cave = NULL;
    while (counter < size)
    {
        if (flag == -1 && content[counter] == '\x00')
        {
            flag = 1;
            x = 0;
        }
        else if (flag == 1 && content[counter] != '\x00')
        {
            flag = -1;
            if (x > 20)
                cave = push_cave(cave, counter - x, counter - (counter - x));
            x = 0;
        }
        if (flag == 1)
            x++; 
        counter++;
    }
    return (cave);
}

void        print_caves(t_cave *cave, unsigned char *content)
{
    t_cave  *trav;

    trav = cave;
    while (trav)
    {
        printf("Start : %zu\n", trav->start_index);
        int counter = 0;
        printf("==========================\n");
        while (counter < trav->content_size)
        {
            if (content[trav->content_size] == 0)
                printf("-");
            else
                printf("x");
            counter++;
        }
        printf("===========================\n\n");
        trav = trav->next;
    }
}
t_cave  *largest_cave(t_cave *caves)
{
    t_cave  *largest;
    t_cave  *trav;

    trav = caves;
    largest = caves->next->next->next->next->next->next;
    return (largest);
    
    while (trav)
    {
        if (trav->content_size > largest->content_size)
            largest = trav;
        trav = trav->next;
    }
    return (largest);
}

size_t  text_vaddr;

void    inspect_main(struct load_command *loader, t_cave *largest, unsigned char *content)
{
    struct entry_point_command  *main;
    
    main = (struct entry_point_command *)loader;

    printf("entryoff : %llu\n", main->entryoff);
    printf("start_index : %zu\n", largest->start_index);
    main->entryoff = largest->start_index;
    int counter =0 ;
    while (counter < 30)
    {
        printf("%x ", content[largest->start_index+counter]);
        counter++;
    }
}

int    edit(unsigned char *content, struct load_command *loader, t_cave *largest)
{
    struct segment_command_64 *segment64;

    segment64 = (struct segment_command_64 *)loader;
    if (strcmp(segment64->segname, "__TEXT") != 0)
        return -1;
    struct section_64 *section64;
    printf("__OTEXT offset %llu\n", segment64->fileoff);
    section64 = (struct section_64 *)&segment64[1];
    int counter = 0;
   
    while (counter < segment64->nsects)
    {
        if (strcmp(section64->sectname, "__text") == 0)
        {
            size_t distance = largest->start_index - section64->offset;
            printf("text address : %llu\n", section64->addr);
            printf("text offset : %u\n",section64->offset);
           // section64->offset = distance;
;
            
            return (1);
        }
        section64 = (struct section_64 *)((void *)section64 + sizeof(struct section_64));
        counter++;
    }
    return (-1);
}

void    edit_text_start_point(unsigned char *content, t_cave *largest)
{
    struct mach_header_64 *header;
    struct load_command *loader;
    int counter;

    header = (struct mach_header_64 *)content;
    loader = (struct load_command *)&header[1];
    counter = 0;
    while (counter < header->ncmds)
    {
        if (loader->cmd == LC_SEGMENT_64)
        {
           edit(content, loader, largest);
        }
        if (loader->cmd == LC_MAIN)
            inspect_main(loader, largest, content);
        if (loader->cmd == LC_UNIXTHREAD)
            printf("unixthread\n");
        loader = (struct load_command *)((void *)loader + loader->cmdsize);
        counter++;
    }
}

void    write_shellcode(t_cave *cave, unsigned char *content)
{
    unsigned char *position;

    position = &content[cave->start_index];

    // hello world execution code.
    char bytes[] = "\xeb\x16\xb8\x04\x00\x00\x02\xbf\x01\x00\x00\x00\x5e\xba\x0c\x00\x00\x00\x0f\x05\x90\x90\xeb\x11\xe8\xe5\xff\xff\xff\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x6c\x64\x0a\x48\xb8\xe8\x11\x00\x00\x01\x00\x00\x00\xff\xe0";
    printf("sie  of bytse is %lu\n", sizeof(bytes));
     memcpy(position, bytes, sizeof(bytes));
}

int     main(int argc, char **argv)
{
    unsigned char   *content;
    size_t          size;
    t_cave          *largest;
    int             fd;
    t_cave          *cave;
    t_cave          *second_largest;

    if (argc != 2)
    {
        printf("Usage : %s [filename]\n", argv[0]);
        return (-1);
    }
    map_file(argv[1], &content, &size);
    cave = code_caves(content, size);
    largest = largest_cave(cave);

    second_largest = cave->next->next->next->next->next;
    largest->start_index += 3;
    printf("printing caves\n");
    print_caves(cave, content);
    write_shellcode(largest, content);

    printf("second largset : %zu\n", second_largest->start_index);

    printf("largest cave : %zu\n", largest->content_size);
    
    edit_text_start_point(content, largest);
    fd = open("fake", O_RDWR | O_CREAT | O_TRUNC, 0777);
    write(fd, content, size);


    close(fd); 
    return (0);
}


