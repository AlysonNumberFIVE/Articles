
#include "packer.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <sys/stat.h>

t_format    *segment = NULL;
size_t  set_point = 9;
size_t  into_file = 0;
size_t  text_section_start = 0;
size_t file_offset = 0;
int     mfd = 0;

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

int	check_file_type(unsigned char *content) 
{
	struct mach_header *header;

	header = (struct mach_header *)content;
	if (header->magic == MH_MAGIC || header->magic == MH_MAGIC_64)
		return (header->magic);
	printf("Error: not an OSX binary file.\n");
	exit(1);
}


void    packer64(unsigned char *content, size_t size)
{
    struct load_command *loader;
    struct mach_header_64 *header64;
    int load_counter = 0;
    int single_increment = 0;
    size_t  load_comm_index = 0;

    header64 = (struct mach_header_64 *)content;
    segment = push_segment(segment, load_comm_index,
        load_comm_index + sizeof(struct mach_header),
        content, "MACH_HEADER");

    loader = (struct load_command *)&header64[1];
    load_comm_index += sizeof(struct mach_header);
    // add the header's size to start us off.
    file_offset += sizeof(struct mach_header_64);
    while (load_counter < header64->ncmds) 
    {
        //print_load_command_names(loader->cmd);
        segment = push_segment(segment, load_comm_index,
            load_comm_index + loader->cmdsize,
            content,  "LOAD_COMMAND");
        if (loader->cmd == LC_SEGMENT_64)
           handle_segment_64(loader, content); 
        if (loader->cmd == LC_DYLD_INFO_ONLY)
            handle_dyld_info_comamnd(loader, content);
        if (loader->cmd == LC_SYMTAB)
        {
            save_current_string_tabe(loader, content);
            //handle_symtab_command(loader);
        }
        if (loader->cmd == LC_DYSYMTAB)
            handle_dysymtab_command(loader);
        if (loader->cmd == LC_FUNCTION_STARTS)
            handle_linkedit_data_command(loader, content);
 
        loader = (struct load_command *)((void*)loader + loader->cmdsize);
        load_comm_index += loader->cmdsize;
        load_counter += 1;
    }
    merge_sort(&segment); 
    seg_length(segment);
}

	
int		main(int argc, char **argv) 
{
	if (argc != 2) 
	{
		printf("Usage : %s [target binary file]\n", argv[0]);
		return -1;
    }
	unsigned char *file_content;
	size_t file_size;
	int		platform_type;

	map_file(argv[1], &file_content, &file_size);
	platform_type = check_file_type(file_content);
	if (platform_type == MH_MAGIC)
		printf("Mach-O 32 bit binary file detected\n");
	else
    {
        mfd = open("modified_binary", O_RDWR | O_CREAT | O_TRUNC, 0777);
        packer64(file_content, file_size);
		printf("Mach-o 64 bit binary file detected\n");
        write(mfd, &file_content[into_file],  file_size - into_file);
        close(mfd);
    }
    return (0); 
}






