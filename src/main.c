#include "file_util.h"
#include "debug_print.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    if(argc < 2){
        debug_print("Give an arg\n");
        return 0xdead;
    }
    struct EntireFile file;
    int res = ReadEntireFile(argv[1],&file);
    debug_print("File size: %zu\n",file.size);
    free(file.buf);
    return res;
}
