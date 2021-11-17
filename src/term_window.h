#ifndef TERM_WINDOW_H
#define TERM_WINDOW_H
#include<GLFW/glfw3.h>
#include<stdint.h>

#ifdef __cplusplus
    extern "C" { 
#endif 

enum TermWindowHint {
    TERM_GL_WINDOW,
    TERM_VULKAN_WINDOW,
    TERM_NO_API
};

struct TermWindow {
    GLFWwindow *m_window;
    uint32_t height;
    uint32_t width;
};

int CreateTermWindow(struct TermWindow *window,uint32_t width,uint32_t height,const char *window_title,enum TermWindowHint hint);
void WindowPollEvents();
void WindowWaitEvents();
int DestroyWindow(struct TermWindow *window);

#ifdef __cplusplus
    } 
#endif

#endif