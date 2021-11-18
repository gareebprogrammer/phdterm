#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H
#include<stdio.h>

#ifdef __cplusplus
    extern "C" { 
#endif

#if _DEBUG
#define debug_print(...)  printf(__VA_ARGS__)
#else
#define debug_print(...)
#endif

#ifdef __cplusplus
    } 
#endif

#endif
