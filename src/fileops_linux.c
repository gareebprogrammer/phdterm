#include "file_ops.h"
#include <sys/stat.h>
#include "debug_print.h"

int GetDiskFileSize(const char *path,size_t *file_size)
{
    struct stat stat_buf;
    if(stat(path,&stat_buf) == -1)
    {
        debug_print("File:%s:%d stat failed path: %s\n",__FILE__,__LINE__,path);
        return 0;
    }
    *file_size = stat_buf.st_size;
    return 1;
}

