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
    FILE *file = fopen(path,"rb");
    if(!file) {
        debug_print("fopen error\n");
        return 0;
    }
    
    file_buf->buf = malloc(file_size+1); 
    if(!file_buf->buf) {
        debug_print("allocation error\n");
        return 0;
    }
    file_buf->size = file_size;
    size_t read_count = fread(file_buf->buf,file_size,1,file);
    if(read_count != 1) {
      debug_print("fread failed\n");
      free(file_buf->buf);
      return 0;
    }
    fclose(file);
    return 1;
}
