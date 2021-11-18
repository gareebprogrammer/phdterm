#include "file_util.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug_print.h"

int ReadEntireFile(const char *path,struct EntireFile *file_buf)
{
    size_t file_size = 0;
    int res = GetDiskFileSize(path,&file_size);
    if(!res){
        return 0;
    }
    debug_print("File size: %d\n", file_size);
    FILE *file = fopen(path,"rb");
    if(!file){
        debug_print("File: %s Line:%d : fopen failed\n",__FILE__,__LINE__);
        return 0;
    }
    file_buf->buf = malloc(sizeof(file_size+1));
    if(!file_buf->buf){
        debug_print("File: %s Line:%d : Allocation failed\n",__FILE__,__LINE__);
        return 0;
    }
    file_buf->size = file_size;
    fread(file_buf->buf,file_size,1,file);
    if(file){
        fclose(file);
    }
    return 1;
}
