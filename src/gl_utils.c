#include "gl_utils.h"
#include <stdio.h>

void PrintGLInfo()
{
    const unsigned char *version = glGetString(GL_VERSION);
    const unsigned char *vendor = glGetString(GL_VENDOR);
    const unsigned char *renderer = glGetString(GL_RENDERER);
    const unsigned char *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GL version: %s\nGL vendor: %s\nGL Renderer: %s\nGlsl version: %s\n",version,vendor,renderer,glsl_version);
}




