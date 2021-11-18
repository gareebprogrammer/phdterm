#include "file_util.h"
#include "debug_print.h"

int main(int argc,char *argv[]){
    struct EntireFile file;
    int res = ReadEntireFile("CMakeCache.txt",&file);
    if(!res){
        debug_print("Read failed\n");
        return 0xdead;
    }
    debug_print("%s\n",(char *)file.buf);
}
