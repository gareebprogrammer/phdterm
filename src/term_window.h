#ifndef TERM_WINDOW_H
#define TERM_WINDOW_H
#include<GLFW/glfw3.h>
#include<stdint.h>

#ifdef __cplusplus
    extern "C" { 
#endif 

enum TermWindowType {
    TERM_GL_WINDOW,
    TERM_VULKAN_WINDOW,
    TERM_NO_API
};

struct TermWindow {
    GLFWwindow *m_window;
    uint32_t height;
    uint32_t width;
    enum TermWindowType window_type;
};

int CreateTermWindow(struct TermWindow *window,uint32_t width,uint32_t height,const char *window_title,enum TermWindowType hint);
void WindowPollEvents();
void WindowWaitEvents();
int IsWindowOpen(struct TermWindow *window);
void WindowSwapBuffers(struct TermWindow *window);
void CloseWindow(struct TermWindow *window);
int DestroyWindow(struct TermWindow *window);

#ifdef __cplusplus
    } 
#endif

#endif
