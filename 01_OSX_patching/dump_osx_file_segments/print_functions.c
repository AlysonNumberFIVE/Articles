


#include "packer.h"
#include <stdio.h>
#include <mach-o/loader.h>


void    print_load_command_names(int load_name)
{
    if (load_name == LC_SEGMENT) 
        printf("LC_SEGMENT\n");
    else if (load_name == LC_SYMTAB) 
        printf("LC_SYMTAB\n");
    else if (load_name == LC_SYMSEG) 
        printf("LC_SYMSEG\n");
    else if (load_name == LC_THREAD) 
        printf("LC_THREAD\n");
    else if (load_name == LC_UNIXTHREAD)
        printf("LC_UNIXTHREAD\n");
    else if (load_name == LC_LOADFVMLIB)
        printf("LC_LOADFVMLIB\n");
    else if (load_name == LC_IDFVMLIB)
        printf("LC_IDFVMLIB\n");
    else if (load_name == LC_IDENT)
        printf("LC_IDENT\n");
    else if (load_name == LC_FVMFILE)
        printf("LC_FVMFILE\n");
    else if (load_name == LC_PREPAGE)
        printf("LC_PREPAGE\n");
    else if (load_name == LC_DYSYMTAB)
        printf("LC_DYSYMTAB\n");
    else if (load_name == LC_LOAD_DYLIB)
        printf("LC_LOAD_DYLIB\n");
    else if (load_name == LC_ID_DYLIB)
        printf("LC_ID_DYLIB\n");
    else if (load_name == LC_LOAD_DYLINKER)
        printf("LC_LOAD_DYLINKER\n");
    else if (load_name == LC_ID_DYLINKER)
        printf("LC_ID_DYLINKER\n");
    else if (load_name == LC_PREBOUND_DYLIB)
        printf("LC_PREBOUND_DYLIB\n");
    else if (load_name == LC_ROUTINES)
        printf("LC_ROUTINES\n");
    else if (load_name == LC_SUB_FRAMEWORK)
        printf("LC_SUB_FRAMEWORK\n");
    else if (load_name == LC_SUB_CLIENT)
        printf("LC_SUB_CLIENT\n");
    else if (load_name == LC_SUB_LIBRARY)
        printf("LC_SUB_LIBRARY\n");
    else if (load_name == LC_TWOLEVEL_HINTS)
        printf("LC_TWOLEVEL_HINTS\n");
    else if (load_name == LC_PREBIND_CKSUM)
        printf("LC_PREBIND_CHECKSUM\n");
    else if (load_name == LC_LOAD_WEAK_DYLIB)
        printf("LC_LOAD_WEAK_DYLIB\n");
    else if (load_name == LC_SEGMENT_64)
        printf("LC_SEGMENT_64\n");
    else if(load_name == LC_ROUTINES_64)
        printf("LC_ROUTINES_64\n");
    else if (load_name == LC_UUID)
        printf("LC_UUID\n");
    else if (load_name == LC_RPATH)
        printf("LC_RPATH\n");
    else if (load_name == LC_CODE_SIGNATURE)
        printf("LC_CODE_SIGNATURE\n");
    else if (load_name == LC_SEGMENT_SPLIT_INFO)
        printf("LC_SEGMENT_SPLIT_INFO\n");
    else if (load_name == LC_REEXPORT_DYLIB)
        printf("LC_REEXPORT_DYLIB\n");
    else if (load_name == LC_LAZY_LOAD_DYLIB)
        printf("LC_LAZY_LOAD_DYLIB\n");
    else if (load_name == LC_ENCRYPTION_INFO)
        printf("LC_ENCRYPTION_INFO\n");
    else if (load_name == LC_DYLD_INFO)
        printf("LC_DYLD_INFO\n");
    else if (load_name == LC_DYLD_INFO_ONLY)
        printf("LC_DYLD_INFO_ONLY\n");
    else if (load_name == LC_LOAD_UPWARD_DYLIB)
        printf("LC_LOAD_UPWARD_DYLIB\n");
    else if(load_name == LC_VERSION_MIN_MACOSX)
        printf("LC_VERSION_MIN_MACOSX\n");
    else if (load_name == LC_VERSION_MIN_IPHONEOS)
        printf("LC_VERSION_MIN_IPHONEOS\n");
    else if (load_name == LC_FUNCTION_STARTS)
        printf("LC_FUNCTION_STARTS\n");

}
