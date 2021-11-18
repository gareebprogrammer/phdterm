#include "file_util.h"
#include "debug_print.h"
#include <stdio.h>

int main(int argc,char *argv[]){
    struct EntireFile file;
    int res = ReadEntireFile("CMakeCache.txt",&file);
    char *ptr = (char *)file.buf;
    printf("%s\n", ptr);
    free(file.buf);
    return res;
}
